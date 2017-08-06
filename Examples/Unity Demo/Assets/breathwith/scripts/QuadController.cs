using UnityEngine;

public class QuadController : MonoBehaviour {

    BreatheController bc;

    // Use this for initialization
    void Start()
    {
        var bw = GameObject.Find("BreatheWith");
        if (bw && bw.activeSelf)
            bc = bw.GetComponent<BreatheController>();
    }

    // Update is called once per frame
    void Update()
    {
        if (bc)
        {
            var scale = Mathf.Max(1f, bc.currReading / 50f - 6.0f);
            var currPos = transform.localPosition;
            transform.localPosition = new Vector3(currPos.x, currPos.y, scale);
        }
    }
}
