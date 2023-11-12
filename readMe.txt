HHP%%#%%%%%%%%%%%%%%%%#%%%%%%%#%%VHH
dHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHb
██████╗  ██████╗ ██╗     ██╗  ██╗   ██╗
██╔══██╗██╔═══██╗██║     ██║  ╚██╗ ██╔╝
██████╔╝██║   ██║██║     ██║   ╚████╔╝ 
██╔═══╝ ██║   ██║██║     ██║    ╚██╔╝  
██║     ╚██████╔╝███████╗███████╗██║   
╚═╝      ╚═════╝ ╚══════╝╚══════╝╚═╝   
dHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHb    
HHP%%#%%%%%%%%%%%%%%%%#%%%%%%%#%%VHH
HH%%%%%%%%%%#%v~~~~~~\%%%#%%%%%%%%HH
HH%%%%%#%%%%v'        ~~~~\%%%%%#%HH
HH%%#%%%%%%v'dHHb      a%%%#%%%%%%HH
HH%%%%%#%%v'dHHHA     :%%%%%%#%%%%HH
HH%%%#%%%v' VHHHHaadHHb:%#%%%%%%%%HH
HH%%%%%#v'   `VHHHHHHHHb:%%%%%#%%%HH
HH%#%%%v'      `VHHHHHHH:%%%#%%#%%HH
HH%%%%%'        dHHHHHHH:%%#%%%%%%HH
HH%%#%%        dHHHHHHHH:%%%%%%#%%HH
HH%%%%%       dHHHHHHHHH:%%#%%%%%%HH
HH#%%%%       VHHHHHHHHH:%%%%%#%%%HH
HH%%%%#   b    HHHHHHHHV:%%%#%%%%#HH
HH%%%%%   Hb   HHHHHHHV'%%%%%%%%%%HH
HH%%#%%   HH  dHHHHHHV'%%%#%%%%%%%HH
HH%#%%%   VHbdHHHHHHV'#%%%%%%%%#%%HH
HHb%%#%    VHHHHHHHV'%%%%%#%%#%%%%HH
HHHHHHHb    VHHHHHHH:%odHHHHHHbo%dHH
HHHHHHHHboodboooooodHHHHHHHHHHHHHHHH
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
VHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHV


            _____                
______________  /____  _________ 
__  ___/  _ \  __/  / / /__  __ \
_(__  )/  __/ /_ / /_/ /__  /_/ /
/____/ \___/\__/ \__,_/ _  .___/ 
                        /_/
First make sure you are on 64bit Fedora or Debian/Ubuntu based Linux distro
    (works best on Ubuntu or CentOS)

Then install the following:

* python3.10
* g++
* flask
* pytorch
* transformers
* curl
* espeak
* openssl-devel
* portaudio-devel

Please ensure all the above packages are added to PATH before proceeding.

       _____              _____ 
_________  /______ _________  /_
__  ___/  __/  __ `/_  ___/  __/
_(__  )/ /_ / /_/ /_  /   / /_  
/____/ \__/ \__,_/ /_/    \__/  
Open two terminals, turn your volume on, then enter these commands:

1. python3 llm_service.py (opens server..MUST KEEP IT RUNNING)
2. (in new terminal) g++ -o Polly Polly.cpp Display.cpp LLMProcessing.cpp TextToSpeech.cpp VoiceCustomization.cpp STT.cpp SpeechRecognizer.cpp -std=c++11 -lcurl -lportaudio -lcrypto -lssl -I.
3. (in the terminal you ran the g++ command) ./Polly


_____            __________                
__  /______________  /___(_)_____________ _
_  __/  _ \_  ___/  __/_  /__  __ \_  __ `/
/ /_ /  __/(__  )/ /_ _  / _  / / /  /_/ / 
\__/ \___//____/ \__/ /_/  /_/ /_/_\__, /  
                                  /____/   
When you see "Polly is listening", you can directly type in your prompts.
For the MVP, the LLM is running using CPU inference, therefore it
takes a little bit of time to generate responses. Please be patient,
and wait for Polly to speak its response and emotion.

Once Polly is done talking, Polly is listening will be prompted again, and you
will be able to continue talking.

To change voice, type "change voice"

To exit, type "shut down"

To try out the Speech-To-Text functionality (STT.cpp), type "test", and begin speaking (no need to enter)
after a set amount of time, you will recieve back what you said in JSON, and after a while, Polly will respond.
	****Please note that this is still in development and may show a bunch of errors/break the program****




