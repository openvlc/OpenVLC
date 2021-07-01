import time

from netmiko import ConnectHandler, NetmikoTimeoutException
from lifi_multicell.constants import devices_ip, devices_user, CiscoSwitch, TPLinkSwitch, BBB
from lifi_multicell.constants import err_no_switch, stop_exec

# Import modules for open a SSH console
from sys import platform

if platform in ['windows', 'win32', 'win64']:
    from subprocess import Popen, CREATE_NEW_CONSOLE  # this can't be imported on Linux
elif platform == 'linux':
    from subprocess import Popen
from shlex import quote

from pexpect import pxssh
import os

class Controller:

    def __init__(self):

        self.switch_dev = TPLinkSwitch()  # select here the switch model
        try:
            self.ch = ConnectHandler(ip=self.switch_dev.info_["address"],
                                     port=self.switch_dev.info_["ssh_port"],
                                     username=self.switch_dev.info_["username"],
                                     password=self.switch_dev.info_["password"],
                                     secret=self.switch_dev.info_["secret"],
                                     device_type=self.switch_dev.info_["device_type"])
        except NetmikoTimeoutException:
            print(err_no_switch)
            print(stop_exec)
            exit()

        self.ssh_sessions = {str(i): False for i in range(36)}
        self.ssh_sessions_status = {str(i): None for i in range(36)}

    # These methods are defined joint for Cisco and TP-Link
    def turn_on_device(self, dev_id):
        """
        Enables power in a port

        :param dev_id: Port ID to enable power on
        :type (int)
        :return:
        """

        if self.switch_dev.info_["device_type"] in ("cisco_ios", "tplink_jetstream"):
            self.ch.enable()
            cmd = [self.switch_dev.if_name.format(dev_id), self.switch_dev.enable_power_port]
            output = self.ch.send_config_set(cmd)
            print(output)
            output = self.ch.send_command(self.switch_dev.show_power_config)
            print(output)
            if self.ch.check_config_mode():
                self.ch.exit_enable_mode(exit_command=self.switch_dev.exit_command)

        else:
            raise Exception("Switch device class unidentified")

    def turn_off_device(self, dev_id):
        """
        Disables power in a port

        :param dev_id: Port ID to disable power on
        :return: 0 if the device was turned off
                 1 if the device wasn't turned off SSH session active
        """

        dev_id_str = str(dev_id)
        # Check for active SSH sessions
        if self.ssh_sessions[dev_id_str]:
            # There is possible an open SSH session in this device. Check.
            if self.ssh_sessions_status[dev_id_str].poll() != 0:
                # SSH session wasn't closed
                return 1
            else:
                # The session was closed. Keep with disabling
                self.ssh_sessions[dev_id_str] = 'False'
                self.ssh_sessions_status[dev_id_str] = None

        # Halt BBB
        if self.halt_device(dev_id_str) == 1:
            # System couldn't be halted
            return 2
        else:
            time.sleep(10)  # Wait until BBB is halted
            # Check with ping if BBB is halted
            if os.system("ping -c 5 " + devices_ip[dev_id_str]) == 256:  # Error code: Destination Host Unreachable
                # System can be powered off
                pass
            else:
                # System was not halted
                return 2

        if self.switch_dev.info_["device_type"] in ("cisco_ios", "tplink_jetstream"):  # Power off system
            self.ch.enable()
            cmd = [self.switch_dev.if_name.format(dev_id), self.switch_dev.disable_power_port]
            output = self.ch.send_config_set(cmd)
            print(output)
            output = self.ch.send_command(self.switch_dev.show_power_config)
            print(output)
            if self.ch.check_config_mode():
                self.ch.exit_enable_mode(exit_command=self.switch_dev.exit_command)
            return 0
        else:
            raise Exception("Switch device class unidentified")

    def halt_device(self, dev_id_str):
        """
        Connects through SSH to a BeagleBone Black, halts the system and exit. It is completed in about 3 seconds

        :param dev_id_str: Port ID to disable power on
        :return: 0 if the process was completed
                 1 otherwise
        """
        try:
            s = pxssh.pxssh()
            s.login(devices_ip[dev_id_str], BBB.bbb_usr, BBB.bbb_pwd)
            s.sendline('sudo halt')
            s.sendline(BBB.bbb_pwd)
            # Logout won't be clean. The device is powered off
            return 0

        except pxssh.ExceptionPxssh as e:
            print("pxssh failed on login.")
            print(e)
            return 1

    def ssh_device(self, dev_id):
        """
        Establish an SSH session with the device in a port

        :param dev_id: Port ID to establish SSH session with
        :type (int)
        :return:
        """
        dev_id_str = str(dev_id)
        if platform in ['windows', 'win32', 'win64']:
            ssh_cmd = "ssh -t -l " + quote(devices_user) + " " + devices_ip[str(dev_id)]
            '''
            -t: forcing a terminal
            In Windows, shell=False (default) works fine (ssh is a executable).
            '''
            status = Popen(ssh_cmd, creationflags=CREATE_NEW_CONSOLE)
            self.ssh_sessions[dev_id_str] = True
            self.ssh_sessions_status[dev_id_str] = status
            print(status)
        elif platform == 'linux':
            '''
            In Linux, xterm is used. This command does not finish to Popen when the window is still open. Unlike
            x-terminal-emulator, which is a symlink to the system terminal.
            shell=True is required: xterm requires args (SSH session to run)
            '''
            ssh_cmd = "xterm -e " + "ssh -l " + quote(devices_user) + " " + devices_ip[str(dev_id)]
            status = Popen(ssh_cmd, shell=True)
            self.ssh_sessions[dev_id_str] = True
            self.ssh_sessions_status[dev_id_str] = status
