using System.IO.Ports;
using System.Collections;

/**
 * This class encapsulates the thread routine that will fetch new COM port readings
 * independent of Unity's Update cycle.
 */
public class SerialThreadWorker {

    string portName;
    int baudRate;
    int maxBufferSize;
    bool keepRunning; // Set to false to stop loop
    Queue messageBuffer;
    SerialPort stream;

    public SerialThreadWorker(string portName, int baudRate, int maxBufferSize) {
        this.portName = portName;
        this.baudRate = baudRate;
        this.maxBufferSize = maxBufferSize;
        messageBuffer = Queue.Synchronized(new Queue());
    }

    // Thread routine to be invoked
    public void Run() {
        stream = new SerialPort(portName, baudRate);
        stream.Open();
        keepRunning = true;
        while (keepRunning) {
            messageBuffer.Enqueue(stream.ReadLine());
            if (messageBuffer.Count > maxBufferSize)
                messageBuffer.Dequeue(); 
        }
        stream.Close();
    }

    // Gets the oldest reading in the current queue
    public object GetReading() {
        if (messageBuffer.Count == 0)
            return null;

        return messageBuffer.Dequeue();
    }

    public void Stop() {
        keepRunning = false;
    }
}
