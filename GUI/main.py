import PySimpleGUI as sg
import serial
import serial.tools.list_ports_windows as list_ports
from threading import Thread
from pynput.keyboard import KeyCode, Listener



sg.theme('DarkGrey1')  

def get_open_ports():
    ports = list_ports.comports()
    print(ports)
    # Returns hardcoded array for testing
    return ["COM1", "COM2", "COM3"]
    return result

layout = [  
    [
        # Control
        sg.Column([
            [sg.Text("Control", font="bold")],
            [sg.Frame("Base", [
                [sg.Button("🡹")],
                [sg.Button("🡸"), sg.Button("🡻"), sg.Button("🡺")],
            ], element_justification="center")],
            [sg.Frame("Arm", [
                [sg.Button("🡹")],
                [sg.Button("Open/Close")],
                [sg.Button("🡻")]
            ], element_justification="center", size=(100, 120), pad=(4))]
        ], element_justification="l", vertical_alignment="top", size=(150, 300)),

        # Information
        sg.Column([
            [sg.Text("Data", font="bold")],
            [sg.Text("Base Rotation: 90", key="base_rot")],
            [sg.Text("Base Hinge Rotation: 90", key="base_hinge_rot")],
            [sg.Text("Hinge Rotation: 90", key="hinge_rot")],
            [sg.Text("Grabber: Open", key="grabber_toggled")]
        ], element_justification="l", vertical_alignment="top", size=(200, 200)),
        
        # Arduino Connection
        sg.Column([
            [sg.Text("Connect to Arduino", font="bold")],
            [sg.Text("COM Port:", justification="left"), sg.DropDown(key="com_port", values=get_open_ports(), size=(8), default_value=get_open_ports()[0], pad=((8)))],
            [sg.Text("Baud Rate:", justification="left"), sg.DropDown(key="baud_rate", values=[300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200], size=((8)), default_value="9600")],
            [sg.Button("Connect", key="connect_btn")],
            [sg.Text("Not Connected", key="connected_text", text_color="red")]
        ], element_justification="l", vertical_alignment="top", size=(200, 220)),

        # Logging
        sg.Column([
            [sg.Text("Logs", font="bold")],
            [sg.Multiline(size=(65, 20), background_color="black", text_color="white", key="multiline_logs", no_scrollbar=False, autoscroll=True)]
        ], visible=False, key="logs", size=(500, 375))

    ],

    # Options
    [sg.Text('Options', font="bold")],
    [sg.Checkbox('Use Keyboard Input', default=False, key="use_kb_input", enable_events=True)],
    [sg.Checkbox("Show Logs", default=False, key="show_logs", enable_events=True)],

    # Stuff
    [sg.Button('Update'), sg.Button('Exit')] 
]

window = sg.Window('Arduino Arm Control', layout, return_keyboard_events=True, use_default_focus=False)
print = lambda *args, **kwargs: window['multiline_logs'].print(*args, **kwargs)

arduino: serial.Serial

# Will be used for controlling arduino with keyboard input
def on_press(key: KeyCode):
    
    #print(f"Key: {key}")

    pass

def key_input():
    listener = Listener(on_press=on_press)
    listener.start()

t = Thread(target=key_input)
t.start()


# Event loop
while True:
    event, values = window.read()
    if event == sg.WIN_CLOSED or event == 'Exit': # if user closes window or clicks cancel
        t.join()
        break
    
    if event == "use_kb_input":
        # Send arduino data telling it to toggle using kb input
        pass
    elif event == "show_logs":
        # Toggle logs

        toggle = values["show_logs"]
        print(toggle)

        window["logs"].update(visible=toggle)

        pass
    elif event == "connect_btn":
        # Connect to arduino
        
        com_port = values["com_port"]
        baud = values["baud_rate"]
        print(f"\nConnecting... \nPORT: {com_port} \nBAUD: {baud}\n")

        try:
            arduino = serial.Serial(port=com_port, baudrate=baud, timeout=.1)
            print("Connected!\n", text_color="green")
        except:
            print("Failed to connect to arduino!\n", text_color="red")
            continue 
        
        v = arduino.write(bytes("PC_CONNECT", "utf-8"))
        print(v)

        window["connected_text"].update("Connected", text_color="green")


window.close()
t.join()
exit()
