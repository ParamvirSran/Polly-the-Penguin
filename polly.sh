#!/bin/bash

# Start Python backend server
echo "Starting Python backend server..."
python3 llm_service.py &
BACKEND_PID=$!

# Build and run the C++ application
echo "Building and running C++ application..."
mkdir -p cmake/build
cd cmake/build
cmake ../..
make
./Polly &
POLLY_PID=$!
cd ../..

# Start Vite for the front-end
echo "Starting Vite server for front-end..."
(cd webui && npx vite) &
VITE_PID=$!

# Wait for a few seconds to ensure servers are up and running
echo "Waiting for servers to start..."
sleep 1

# Open the web application in the default browser
echo "Opening web application in the default browser..."
xdg-open http://localhost:5173/ &

# Instructions for stopping the servers
echo "Servers are running. You can access the web application at http://localhost:5173/"
echo "To stop all servers, run: kill $BACKEND_PID $POLLY_PID $VITE_PID"

# Keep script running until all servers are stopped
wait $BACKEND_PID $POLLY_PID $VITE_PID
