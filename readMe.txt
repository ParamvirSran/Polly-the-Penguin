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

First make sure you are on 64bit Fedora or Debian/Ubuntu 
Then install the following:

* python3.10
* g++
* flask
* pytorch
* transformers


       _____              _____ 
_________  /______ _________  /_
__  ___/  __/  __ `/_  ___/  __/
_(__  )/ /_ / /_/ /_  /   / /_  
/____/ \__/ \__,_/ /_/    \__/  
                                
1. python3 llm_service.py (opens server..MUST KEEP IT RUNNING)
2. (in new terminal) - g++ -o Polly polly.cpp Display.cpp LLMProcessing.cpp TextToSpeech.cpp VoiceCustomization.cpp -std=c++11 -lcurl



_____            __________                
__  /______________  /___(_)_____________ _
_  __/  _ \_  ___/  __/_  /__  __ \_  __ `/
/ /_ /  __/(__  )/ /_ _  / _  / / /  /_/ / 
\__/ \___//____/ \__/ /_/  /_/ /_/_\__, /  
                                  /____/   
currently missing SpeechToText, so you gotta type what you want 
to say in the terminal running Polly (not the py server)




current issues:

due to system() in LLMProcessing to run the curl command to the llm_service, 
currently Polly is only compatible on Windows (untested for Unix-based systems)
