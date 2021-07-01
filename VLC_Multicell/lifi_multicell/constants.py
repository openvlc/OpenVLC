# LiFi lab setup

rows_dev = 7
columns_dev = 5
# IP list and ports
devices_ip = {
    '1': '192.168.10.4',
    '2': '192.168.10.5',
    '3': '192.168.10.6',
    '4': '192.168.10.7',
    '5': '192.168.10.8',
    '6': '192.168.10.9',
    '7': '192.168.10.10',
    '8': '192.168.10.11',
    '9': '192.168.10.12',
    '10': '192.168.10.13',
    '11': '192.168.10.14',
    '12': '192.168.10.15',
    '13': '192.168.10.16',
    '14': '192.168.10.17',
    '15': '192.168.10.18',
    '16': '192.168.10.19',
    '17': '192.168.10.20',
    '18': '192.168.10.21',
    '19': '192.168.10.22',
    '20': '192.168.10.23',
    '21': '192.168.10.24',
    '22': '192.168.10.25',
    '23': '192.168.10.26',
    '24': '192.168.10.27',
    '25': '192.168.10.28',
    '26': '192.168.10.29',
    '27': '192.168.10.30',
    '28': '192.168.10.31',
    '29': '192.168.10.32',
    '30': '192.168.10.33',
    '31': '192.168.10.34',
    '32': '192.168.10.35',
    '33': '192.168.10.36',
    '34': '192.168.10.37',
    '35': '192.168.10.38',
    '36': '192.168.10.39',
}
devices_user = "debian"

# GUI parameters
window_title = "LiFi multi-cell  "  # spaces required to align the window title
width_board = 250
height_board = 350
tile_color = {
    "ON": "yellow",
    "OFF": "red",
    "SSH": "green"
}

# GUI messages
ssh_warning_title = "Active SSH session!"
ssh_warning_msg = "There is still an active SSH session in this device. Close and try again."


# BBB information
class BBB:

    bbb_usr = ''
    bbb_pwd = ''


# Switch configuration
# TP-Link 1600G-52PS
class TPLinkSwitch:

    """
    Information and command syntax for TP-Link T1600-52PS

    If and RSA key is generated, it will be required to check how it will be done
    It its not needed since SSH rely only on password
    """

    info_ = {
        "address": "192.168.10.2",
        "ssh_port": 22,
        "username": "",
        "password": "",  # login
        "secret": "",  # enable
        "device_type": "tplink_jetstream",
        "host": "",
    }

    if_name = "interface gigabitEthernet 1/0/{}"
    exit_command = "exit"

    enable_power_port = "power inline supply enable"
    disable_power_port = "power inline supply disable"
    show_power_port = "show power inline information interface"  # all ports
    show_power_config = "show power inline configuration interface"


# Error messages
err_no_switch = 'PoE Switch is not connected. Please, connect'
stop_exec = 'Stopping execution'
