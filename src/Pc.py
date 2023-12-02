import serial
import time
import crcmod

# Open a serial connection to the MCU
ser = serial.Serial('COMx',2400)  # Replace 'COMx' with the appropriate port and 2400 with your baud rate

# Define the text to be transmitted
text_to_send = "Finance Minister Arun Jaitley Tuesday hit out at former RBI governor Raghuram Rajan for predicting that the next banking crisis would be triggered by MSME lending, saying postmortem is easier than taking action when it was required. Rajan, who had as the chief economist at IMF warned of impending financial crisis of 2008, in a note to a parliamentary committee warned against ambitious credit targets and loan waivers, saying that they could be the sources of next banking crisis. Government should focus on sources of the next crisis, not just the last one In particular, government should refrain from setting ambitious credit targets or waiving loans. Credit targets are sometimes achieved by abandoning appropriate due diligence, creating the environment for future NPAs, Rajan said in the note Both MUDRA loans as well as the Kisan Credit Card, while popular, have to be examined more closely for potential credit risk. Rajan, who was RBI governor for three years till September 2016, is currently."

# Create a CRC- function
# crc32_func = crcmod.mkCrcFun(0x104c11db7, initCrc=0, xorOut=0xFFFFFFFF)
crc16_func = crcmod.mkCrcFun(0x8005, initCrc=0, xorOut=0xFFFF)


# Calculate CRC checksum for the text
crc_checksum = crc16_func(text_to_send.encode())

# Send the text and CRC to the MCU
message_to_send = f"{text_to_send}${crc_checksum}"
ser.write(message_to_send.encode())

# Close the serial connection
ser.close()
