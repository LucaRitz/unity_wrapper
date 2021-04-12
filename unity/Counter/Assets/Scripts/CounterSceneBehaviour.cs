using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CounterSceneBehaviour : MonoBehaviour
{
    void Start() {
        SceneManager.SetActiveScene(SceneManager.GetSceneByName("CounterScene"));
    }
}
