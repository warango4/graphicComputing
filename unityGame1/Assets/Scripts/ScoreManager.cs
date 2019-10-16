using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreManager : MonoBehaviour {

    #region variables
    [SerializeField]
    private Text scoreText;

    int score = 0;
    #endregion

    // Start is called before the first frame update
    void Start() {
        scoreText = transform.GetChild(0).GetChild(0).GetComponent<Text>();
        scoreText.text = score.ToString();
    }

    public void AddScore() {
        scoreText.text = score++.ToString();
    }
}
