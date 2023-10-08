with open("ffmpeg.exe", "rb") as f:
    bytes = f.read()
    with open("ffmpeg_bytes.h", "w") as h:
        h.write("unsigned char ffmpeg_bytes[] = {")
        h.write(','.join(["0x{:02x}".format(byte) for byte in bytes]))
        h.write("};")