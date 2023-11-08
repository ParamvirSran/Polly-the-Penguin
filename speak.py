# speak.py
import pyttsx3
import sys

def main(text):
    engine = pyttsx3.init()
    engine.say(text)
    engine.runAndWait()

if __name__ == "__main__":
    main(sys.argv[1])