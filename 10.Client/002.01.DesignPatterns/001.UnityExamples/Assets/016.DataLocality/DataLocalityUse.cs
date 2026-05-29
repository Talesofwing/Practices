using System.Collections.Generic;
using System.Diagnostics;

using UnityEngine;

using Debug = UnityEngine.Debug;

namespace DesignPattern.DataLocality
{
	public class DataLocalityUse : MonoBehaviour
	{
		private List<DataStruct> _dataStruct = new List<DataStruct>();
		private List<DataStruct2> _dataStruct2 = new List<DataStruct2>();

		private void Start()
		{
			for (int i = 0; i < 10000000; ++i)
			{
				_dataStruct.Add(new DataStruct()
				{
					ID = i,
					Atk = i,
					Defense = i,
					DropItemID1 = i,
					DropItemID2 = i,
					DropItemID3 = i,
					DropItemID4 = i,
					DropItemID5 = i,
					DropItemID6 = i,
					DropItemID7 = i,
					DropItemID8 = i,
					DropItemID9 = i,
					DropItemID10 = i,
					DropItemID11 = i,
					DropItemID12 = i,
					DropItemID13 = i,
					DropItemID14 = i,
					DropItemID15 = i,
					DropItemID16 = i,
					DropItemID17 = i,
					DropItemID18 = i,
					DropItemID19 = i,
					DropItemID20 = i,
				});

				_dataStruct2.Add(new DataStruct2()
				{
					ID = i,
					Atk = i,
					Defense = i,
					Drop = new DropData()
					{
						DropItemID1 = i,
						DropItemID2 = i,
						DropItemID3 = i,
						DropItemID4 = i,
						DropItemID5 = i,
						DropItemID6 = i,
						DropItemID7 = i,
						DropItemID8 = i,
						DropItemID9 = i,
						DropItemID10 = i,
						DropItemID11 = i,
						DropItemID12 = i,
						DropItemID13 = i,
						DropItemID14 = i,
						DropItemID15 = i,
						DropItemID16 = i,
						DropItemID17 = i,
						DropItemID18 = i,
						DropItemID19 = i,
						DropItemID20 = i,
					},
				});
			}

			Stopwatch stopwatch = new Stopwatch();
			stopwatch.Start();
			for (int i = 0; i < _dataStruct.Count; ++i)
			{
				var data = _dataStruct[i];
				int id = data.ID;
				int atk = data.Atk;
				int defense = data.Defense;
			}
			stopwatch.Stop();
			Debug.Log($"Elapsed time: {stopwatch.ElapsedMilliseconds} ms");

			stopwatch.Reset();
			stopwatch.Start();
			for (int i = 0; i < _dataStruct2.Count; ++i)
			{
				var data = _dataStruct2[i];
				int id = data.ID;
				int atk = _dataStruct2[i].Atk;
				int defense = _dataStruct2[i].Defense;
			}
			stopwatch.Stop();
			Debug.Log($"Elapsed time: {stopwatch.ElapsedMilliseconds} ms");
		}
	}
}
