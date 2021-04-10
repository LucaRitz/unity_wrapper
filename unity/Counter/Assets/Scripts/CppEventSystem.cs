using System;
using UnityEngine;
using System.Collections.Generic;
using System.Net;
using System.Text;
using System.IO;
using System.Runtime.InteropServices;

public class CppEventSystem : MonoBehaviour
{
	////////////////////////////////////////////////////////////////////
	//// Public Interface
	////////////////////////////////////////////////////////////////////
	
    public static event Action<CountEvent> OnCountEvent;
	
	void Start() {
		onStart();
		debug((message) => Debug.Log(message));
		
		// Register native events
		onCountEvent((eventParam) => OnCountEvent?.Invoke(map(eventParam)));
	}
	
	void OnApplicationQuit() {
		onTearDown();
	}
	
	void FixedUpdate() {
		processEvents();
	}
	
	////////////////////////////////////////////////////////////////////
	//// Native Interface Declaration
	////////////////////////////////////////////////////////////////////
	
	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	private delegate void CountEventCallback(CountEvent_t eventParam);
	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	private delegate void DebugCallback(string message);
	
	[DllImport("unity_wrapper", CallingConvention = CallingConvention.Cdecl)]
	private static extern void onStart();
	[DllImport("unity_wrapper", CallingConvention = CallingConvention.Cdecl)]
	private static extern void onTearDown();
	[DllImport("unity_wrapper", CallingConvention = CallingConvention.Cdecl)]
	private static extern void processEvents();
	
	[DllImport("unity_wrapper", CallingConvention = CallingConvention.Cdecl)]
	private static extern void onCountEvent([MarshalAs(UnmanagedType.FunctionPtr)] CountEventCallback callback);
	
	[DllImport("unity_wrapper", CallingConvention = CallingConvention.Cdecl)]
	private static extern void debug([MarshalAs(UnmanagedType.FunctionPtr)] DebugCallback callback);
	
	////////////////////////////////////////////////////////////////////
	//// Adapters for native interaction
	////////////////////////////////////////////////////////////////////
	
	[StructLayout(LayoutKind.Sequential)]
	struct CountEvent_t {
		public int counter;
	}
	
	////////////////////////////////////////////////////////////////////
	//// Mapping between adapter and application model
	////////////////////////////////////////////////////////////////////
	
	private CountEvent map(CountEvent_t from) {
		return new CountEvent(from.counter);
	}
}
