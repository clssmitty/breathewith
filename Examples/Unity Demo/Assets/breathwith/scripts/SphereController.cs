using UnityEngine;

public class SphereController : MonoBehaviour {
    
    BreatheController bc;
    new Renderer renderer;
    float scale;

    [SerializeField] Color neutralColor = Color.white;
    [SerializeField] Color exhaleColor = Color.green;

	// Use this for initialization
	void Start () {
        bc = GameObject.Find("BreatheWith").GetComponent<BreatheController>();
        renderer = GetComponent<Renderer>();
    }
	
	// Update is called once per frame
	void Update () {
        scale = bc.currReading / 50f; // Arbitrary scaling to keep the sphere from becoming too large to see
        transform.localScale = new Vector3(scale, scale, scale);
        renderer.material.color = bc.exhaling ? exhaleColor : neutralColor;
    }
}
