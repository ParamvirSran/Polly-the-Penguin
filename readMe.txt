dependency list (you MUST install these on the system where Polly is to be compiled)

python3.10
flask
pyttsx3



To run:
1. start llm_service.py (opens server..MUST KEEP IT RUNNING)
2. then run polly.cpp



current issues:

due to system() in LLMProcessing to run the curl command to the llm_service, 
currently Polly is only compatible on Windows (untested for Unix-based systems)