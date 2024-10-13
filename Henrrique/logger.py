import serial #PySerial needs to be installed
import time # for time

# Generate file name using current date and time
current_local_time = time.localtime()
filename = time.strftime("%d_B_%Y_%Hh_%Mm_%Ss", current_local_time) #24 hour format
filename = 'arduino_' + filename + '_log.csv'
print(f'Created Log File -> {filename}')

# Create a CSV file header

with open(filename, 'w+') as csvFile:
    csvFile.write('Date,Time,Temperature,Light,Magnet,Human\n')

log_count = 1

#Serial

SerialObj = serial.Serial('/dev/ttyUSB0',9600)
# Both Arduino and Python are sharing the serial port
# Opening the serial port from python will reset the arduino
# 3 second delay will allow the Arduino to settle down
time.sleep(3)

# Log continuously to a file by querying the arduino

while 1:
    BytesWritten = SerialObj.write(b'$') # transmit $ to get values from arduino
    time.sleep(0.10) # 10ms delay
    ReceivedString = SerialObj.readline() # Change to receive mode to get data from arduino
    ReceivedString = str(ReceivedString,'utf-8') # Convert bytes to UTF-8 encoded string
    valuesList = ReceivedString.split(',') # split the string to get values
    separator = ','

    log_time_date = time.localtime()
    log_time = time.strftime("%H:%M:%S", log_time_date) #hh:mm:ss
    log_date = time.strftime("%d %B %Y", log_time_date) #dd MonthName Year

    #create a string to write to file
    log_file_text1 = log_date + separator + log_time + separator
    log_file_text2 = valuesList[0] + separator + valuesList[1] + separator + valuesList[2] + separator + valuesList[3]
    log_file_text3 = log_file_text1 + log_file_text2 + '\n'

    # write to file .csv
    with open(filename,'a') as LogFileObj:
        LogFileObj.write(log_file_text3)

    print(log_file_text3)
    log_count = log_count + 1

    time.sleep(1) # sensing interval

SerialObj.close() # close the port


