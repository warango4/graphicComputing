using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BallBehaviour : MonoBehaviour {

    #region Variables
    [SerializeField]
    private float liveTime = 5;
    [SerializeField]
    private float speed = 2;
    [SerializeField]
    private float deadZone = 0.1f;

    private Vector3[] movementPositions;

    private Vector3 pointToMove;
    private int currentPos = 0;

    private ScoreManager scores;
    #endregion

    // Start is called before the first frame update
    void OnEnable() {
        movementPositions = GameObject.FindGameObjectWithTag("Path").GetComponent<BezierPath>().
            GetBezierPoints();
        transform.position = movementPositions[0];
        pointToMove = movementPositions[1];
        currentPos = 1;

        scores = GameObject.FindGameObjectWithTag("UI").GetComponent<ScoreManager>();

        Color randomColor = new Color(Random.Range(0f,1f),Random.Range(0f,1f),Random.Range(0f,1f));
        transform.GetChild(0).GetComponent<MeshRenderer>().material.color = randomColor;

        //StartCoroutine(DestroyBall());
    }

    // Update is called once per frame
    void Update() {
        if(transform.position != pointToMove) {
            Vector3 dir = pointToMove - transform.position;
            transform.position += dir.normalized * speed * Time.deltaTime;
        }

        if (Vector3.Distance(transform.position,pointToMove) <= deadZone) {
            currentPos++;
            if (currentPos > movementPositions.Length - 1) {
                Destroy(this.gameObject);
            }
            if (currentPos < movementPositions.Length) {
                pointToMove = movementPositions[currentPos];
            }
        }
    }

    private void OnCollisionEnter(Collision collision) {
        if (collision.gameObject.tag.Equals("Target")) {
            scores.AddScore();
            Destroy(this.gameObject);
        }else if (collision.gameObject.tag.Equals("Obstacle")) {
            Destroy(this.gameObject);
        }
    }

    //IEnumerator DestroyBall() {
    //    yield return new WaitForSeconds(liveTime);
    //    Destroy(this.gameObject);
    //}
}
