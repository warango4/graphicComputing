using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Obstacle : MonoBehaviour {

    #region variables
    [SerializeField]
    private float MoveSpeed;
    [SerializeField]
    private Vector3 point1;
    [SerializeField]
    private Vector3 point2;
    [SerializeField]
    private float deadZone = 0.1f;
    bool toPoint1 = false;
    Vector3 pointToMove;
    #endregion

    // Start is called before the first frame update
    void OnEnable() {
        transform.position = point1;
        pointToMove = point2;
    }

    // Update is called once per frame
    void Update() {
        if(transform.position != pointToMove) {
            Vector3 dir = pointToMove - transform.position;
            transform.position += dir.normalized * MoveSpeed * Time.deltaTime;
        }

        if (toPoint1) {
            if (Vector3.Distance(transform.position,point1) <= deadZone) {
                pointToMove = point2;
                toPoint1 = !toPoint1;
            }
        } else {
            if(Vector3.Distance(transform.position,point2) <= deadZone) {
                pointToMove = point1;
                toPoint1 = !toPoint1;
            }
        }
    }
}
