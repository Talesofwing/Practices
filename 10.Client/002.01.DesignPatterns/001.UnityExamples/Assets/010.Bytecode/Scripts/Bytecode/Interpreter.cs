using System.Collections.Generic;
using System.Linq;
using UnityEngine;

namespace DesignPattern.Bytecode
{
	public enum Operation : byte
	{
		UseSkill = 0x00,
		PlayEffect = 0x01,
		PlaySound = 0x02,
	}

	public static class Interpreter
	{
		public static void Interpret(byte[] script)
		{
			for (int ip = 0; ip < script.Length; ip += 2)
			{
				Operation opcode = (Operation)script[ip];
				byte arg = script[ip + 1];

				switch (opcode)
				{
					case Operation.UseSkill:
						Debug.Log("UseSkill: ID" + arg);
						break;
					case Operation.PlayEffect:
						Debug.Log("PlayEffect: ID" + arg);
						break;
					case Operation.PlaySound:
						Debug.Log("PlaySound: ID" + arg);
						break;
					default:
						Debug.LogError("Invalid opcode: " + opcode);
						break;
				}
			}
		}
	}
}
