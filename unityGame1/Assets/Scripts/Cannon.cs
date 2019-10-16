using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cannon : MonoBehaviour {

    #region variables
    [SerializeField]
    private GameObject ball;
    
    private Transform ballInstantiatePosition;

    BezierPath path;
    #endregion

    // Start is called before the first frame update
    void Start() {
        path = GameObject.FindGameObjectWithTag("Path").GetComponent<BezierPath>();

        transform.position = path.GetBezierPoints()[0];
    }

    // Update is called once per frame
    void Update() {
        GameObject BallGO;

        if (Input.GetKeyDown(KeyCode.L)) {
            BallGO = Instantiate(ball);
        }

        transform.position = path.GetBezierPoints()[0];
    }
}
