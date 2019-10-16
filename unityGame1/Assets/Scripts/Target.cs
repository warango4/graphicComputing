using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Target : MonoBehaviour {

    #region Variables
    private Vector3 targetPos;

    BezierPath path;
    
    #endregion

    // Start is called before the first frame update
    void OnEnable() {
        path = GameObject.FindGameObjectWithTag("Path").GetComponent<BezierPath>();
        UpdatePosition();
    }

    // Update is called once per frame
    void Update() {
        UpdatePosition();
    }

    void UpdatePosition() {
        targetPos = path.GetBezierPoints()[path.GetBezierPointsLength()-1];

        transform.position = targetPos;
    }
}
