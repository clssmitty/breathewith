using UnityEngine;
using System.Threading;

/**
 * This class runs the SerialThreadWorker thread routine to capture and store COM port readings.
 * The readings are stored in public variables to be used elsewhere in the scene.
 */
public class BreatheController : MonoBehaviour {

    // Publicly readeable data parsed from COM port readings
    public int currReading;
    public bool exhaling;

    // COM port configs
    [SerializeField] string portName = "COM6";
    [SerializeField] int baudRate = 9600;

    /**
     * The thread worker's internal queue will store the last X readings as specified here.
     * If the user is only interested in the absolute latest COM port reading each time,
     * it would be best to leave this at a minimum of 2 or 3. Otherwise, it might be possible
     * to attempt a read while the queue is empty.
     */ 
    [SerializeField] int maxBufferSize = 3;

    Thread serialThread;
    SerialThreadWorker serialThreadWorker;

    // Initialization
    void Start() {
        serialThreadWorker = new SerialThreadWorker(portName, baudRate, maxBufferSize);
        serialThread = new Thread(new ThreadStart(serialThreadWorker.Run));
        serialThread.Start();
    }

    // Executed each frame
    void Update() {
        string message = (string)serialThreadWorker.GetReading();
        if (message == null)
            return;

        // Parse and store the raw reading
        string[] result = message.Split(',');
        currReading = int.Parse(result[0]);
        exhaling = result[1] == "1";
    }

    private void OnApplicationQuit() {
        serialThreadWorker.Stop();
        serialThread.Join();
    }
}