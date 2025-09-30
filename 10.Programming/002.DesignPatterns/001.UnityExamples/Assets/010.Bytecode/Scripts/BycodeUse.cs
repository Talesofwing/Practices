using System;
using System.IO;
using System.Collections.Generic;

using UnityEngine;

namespace DesignPattern.Bytecode
{
	public class BytecodeUse : MonoBehaviour
	{
		private void Start()
		{
			/*
				0 1
				1 1
				2 1
			*/
			byte[] bytes = { 0x00, 0x01, 0x01, 0x01, 0x02, 0x01 };

			Interpreter.Interpret(bytes);
		}
	}
}
