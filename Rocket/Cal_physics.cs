using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Unity.MLAgents;   //추가

//MonoBehaviour 클래스를 Agent 클래스로 변경
public class Cal_physics : Agent
{
    // //속도가 빨라지면 빨간색, 느려지면 파란색
    // public Material fastWheelMaterial;
    // public Material slowWheelMaterial;

    //private 호출하면 AtoRocket_real을 의미
    private Transform tr;
    private Rigidbody rb;   //강체 : 어떤 힘을 가하여도 모양과 부피가 변하지 않는다고 가상되는 이상적인 고체
    private MeshRenderer mr;

    public Vector3 com;     //벡터로 x,y,z 위치정보를 나타내는 float 3개로 구성된 구조체
    public Transform targetTr;
    public GameObject spinMotor;    //spin_launcher
    public Rigidbody spinRd;
    public RectTransform canvasRtr;
    
    public Text velocityText;
    public Text massText;
    public Text Centerforce;
    public Text MotorSpeed;

    float ang_velocity; //각속도
    private float Centerforce_re; //원심력
    private float mass; //로켓무게
    public float R_radius_distance; //반지름
    // public float speed; //속력
    
     
    //초기화 작업을 위해 한번 호출되는 메소드 - Awake/Start
    public override void Initialize()
    {
        tr = GetComponent<Transform>();
        rb = GetComponent<Rigidbody>();
        mr = GetComponent<MeshRenderer>();
        canvasRtr = GetComponent<RectTransform>();

        // //다시 start하면, 로켓이 제자리로 이동, centerOfMass : transform 원점에 대한 질량의 중심
        // rb.centerOfMass = com;  //에피소드로 옮겨야 할듯

        //에피소드(학습단위) 별 무작위 액션 최대횟수 설정
        //예) 10인 경우, 한번 시작 시, 10번 에피소드 수행 의미 
        MaxStep = 10;

        // //개발자가 고정해주는 값 : 로켓무게
        // mass = rb.mass;     
        // massText.text = "Rocket Mass: " + mass; //에피소드로 옮겨야 할듯

        // //!! 추후 학습될 값
        // velocityText.text = "Angular Velocity: " + ang_velocity; //에피소드로 옮겨야 할듯
        // //!! 추후 학습될 ang_velocity에 의해 계산될 값
        // Centerforce.text = "Center Force: " + Centerforce_re;    //에피소드로 옮겨야 할듯
    }
   
    //에피소드(학습단위)가 시작할때마다 호출
    public override void OnEpisodeBegin()
    {
        //물리력을 초기화
        rb.velocity = Vector3.zero;
        rb.angularVelocity = Vector3.zero;

        //로켓(에이전트) 처음 자리로 이동, centerOfMass : transform 원점에 대한 질량의 중심
        rb.centerOfMass = com; 

        //개발자가 고정해주는 값 : 로켓무게
        mass = rb.mass;     
        massText.text = "Rocket Mass: " + mass;

        spin_around();
        MotorSpeed.text = "Motor Speed: " + speed;
        
        ang_velocity = rb.angularVelocity.magnitude;
        velocityText.text = "Angular Velocity: " + ang_velocity;
        var Centerforce_re = mass * R_radius_distance * ang_velocity * ang_velocity;
        Centerforce.text = "Center Force: " + Centerforce_re;

        StartCoroutine(RevertMaterial());
    }

    void spin_around()
    {
        //transform.RotateAround(회전할 기준 좌표(point), 회전할 기준 축(axis), 회전할 각도(angle))
        transform.RotateAround(spinMotor.transform.position, Vector3.down, speed * Time.deltaTime);
    }

    IEnumerator RevertMaterial()
    {
        yield return new WaitForSeconds(0.2f);  //0.2초 기다림
        //성공하면 target 색깔 구분하자! 예) 오리지널 / 노랑 / 검정
    }

    //환경 정보를 관측 및 수집해 정책 결정을 위해 브레인에 전달하는 메소드
    public override void CollectObservations(Unity.MLAgents.Sensors.VectorSensor sensor)
    {
        sensor.AddObservation(targetTr.localPosition);  //3 (x,y,z)
        sensor.AddObservation(tr.localPosition);        //3 (x,y,z)
        sensor.AddObservation(rb.velocity);             //3 (x,y,z)
        //관측 데이터의 size인 9를 Behaviour Parameters 컴포넌트의 Vector Observation/Space Size 속성 설정 
    }

    //브레인(polocy)으로부터 전달받은 액션(행동)을 실행하는 메소드
    //OnActionReceived : 이동처리 로직
    public override void OnActionReceived(float vectorAction)
    {
        //회전하기 때문에 velocity, speed 등을 정규회해야할듯. 더 수정할 부분

        //데이터를 정규화
        float v = Mathf.Clamp(vectorAction, -1.0f, 1.0f);
        Vector3 dir = (Vector3.forward * v);
        spinRd.speed.AddForce(dir.normalized * 50.0f);    //Force mode를 지정하면 변경가능한 상황으로 바뀜. 아마 학습에 쓰이는 듯

        //지속적으로 이동을 이끌어내기 위한 마이너스 보상
        SetReward(-0.001f);
    }

    //개발자(사용자)가 직접 명령을 내릴때 호출하는 메소드(주로 테스트용도 또는 모방학습에 사용)
    public override void Heuristic(float actionsOut)
    {
        actionsOut = Input.GetAxis("Vertical");    //상, 하 화살표 키  //연속적인 값, -1.0 ~ 0.0 ~ 1.0
        Debug.Log($"[0]={actionsOut}");
    }
    //ㅋㅋㅋㅋㅋㅋ 파란색 머리가 움직인다.

    void OnCollisionEnter(Collision coll)
    {
        if(coll.collider.CompareTag("DEAD_ZONE"))
        {
            //잘못된 액션일 때 마이너스 보상을 준다.
            SetReward(-1.0f);
            //학습을 종료시키는 메소드
            EndEpisode();
        }

        if(coll.collider.CompareTag("TARGET"))
        {
            //올바른 액션일 때 플러스 보상을 준다.
            SetReward(+1.0f);
            //학습을 종료시키는 메소드
            EndEpisode();
        }
    }

    // //Update() :  유니티 내부 이벤트함수, 1개의 Frame이 실행될 때 1번씩 호출된다.
    // void Update()
    // {
    //     //rb.angularVelocity.magnitude : 강체 각속도 크기
    //     //나중에 구현가능하면 하자
    //     if (rb.angularVelocity.magnitude < 5)
    //     {
    //         mr.sharedMaterial = slowWheelMaterial;
    //         ang_velocity = rb.angularVelocity.magnitude;
    //         //Debug.Log("velocity < 5 :" + ang_velocity);
    //         velocityText.text = "Angular Velocity: " + ang_velocity;
    //         var Centerforce_re = mass * R_radius_distance * ang_velocity * ang_velocity;
    //         //Debug.Log("CenterForece:" + Centerforce);
    //         Centerforce.text = "Center Force: " + Centerforce_re;
    //     }
    //     else
    //     {
    //         mr.sharedMaterial = fastWheelMaterial;
    //         ang_velocity = rb.angularVelocity.magnitude;
    //         //Debug.Log("velocity > 5 :" + ang_velocity);
    //         velocityText.text = "Angular Velocity: " + ang_velocity;
    //         var Centerforce_re = mass * R_radius_distance * ang_velocity * ang_velocity;
    //         //Debug.Log("CenterForece:" + Centerforce);
    //         Centerforce.text = "Center Force: " + Centerforce_re;
    //     }
    // }
}