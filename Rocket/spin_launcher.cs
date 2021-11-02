using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class spin_launcher : MonoBehaviour
{

    public GameObject motor;
    public float speed;
    public Text MotorSpeed;    


    // Start is called before the first frame update
    void Start()
    {
        RectTransform rectTransform;
        rectTransform = GetComponent<RectTransform>();
    }

    // Update is called once per frame
    void Update()
    {
        spin_around();
        MotorSpeed.text = "Motor Speed: " + speed;
        
    }

    void spin_around()
    {
        transform.RotateAround(motor.transform.position, Vector3.down, speed * Time.deltaTime);
    }
}