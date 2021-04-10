using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class CounterBehaviour : MonoBehaviour
{
	public TextMeshPro counterText;
	
	private int counter = 0;
	
    void Start() {
		// Register events
		CppEventSystem.OnCountEvent += onCountEvent;
    }

    void Update() {
        counterText.SetText(counter.ToString());
    }
	
	private void onCountEvent(CountEvent eventParam) {
		counter = eventParam.counter;
	}
}
