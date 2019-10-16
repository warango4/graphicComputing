using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class BezierPath : MonoBehaviour {

    #region variables
    [SerializeField]
    private Vector3[] ControlPoints = new Vector3[4];

    [SerializeField]
    private int segments = 10;

    [SerializeField]
    private Vector3[] bezierpoint;
    #endregion

    // Start is called before the first frame update
    void Start() {
        SetupCurve();
        
    }

    #region BezierCalculations
    void SetupCurve() {
        bezierpoint = new Vector3[segments + 1];

        float step = 1f / segments;

        float u = 0;
        for (int i = 0; i <= segments; i++) {
            bezierpoint[i] = Bezier(u,ControlPoints.Length - 1);
            u += step;
        }
    }

    Vector3 Bezier(float u, int n) {
        float acumX = 0;
        float acumY = 0;
        float acumZ = 0;
        for (int i = 0; i < ControlPoints.Length; i++) {
            float blend = Blending(u,n,i);
            acumX += ControlPoints[i].x * blend;
            acumY += ControlPoints[i].y * blend;
            acumZ += ControlPoints[i].z * blend;
        }
        return new Vector3(acumX,acumY,acumZ);
    }

    float Blending(float u, int n, int k) {
        return Coefficient(n,k) * Mathf.Pow(u,k) * Mathf.Pow(1 - u,n - k);
    }

    int Coefficient (int n, int k) {
        return Factorial(n) / (Factorial(k) * Factorial(n - k));
    }

    int Factorial (int value){
        int accum = 1;
        for(int i = 1; i <= value; i++) {
            accum *= i;
        }
        return accum;
    }
    #endregion

    //Called each time the editor is modified
    void OnValidate() {
        SetupCurve();
    }

    public Vector3[] GetBezierPoints() {
        return bezierpoint;
    }

    public int GetBezierPointsLength() {
        return segments + 1;
    }
}
