namespace DesignPattern.DataLocality
{
	public struct DataStruct
	{
		public int ID;
		public int Atk;
		public int Defense;

		public int DropItemID1;
		public int DropItemID2;
		public int DropItemID3;
		public int DropItemID4;
		public int DropItemID5;
		public int DropItemID6;
		public int DropItemID7;
		public int DropItemID8;
		public int DropItemID9;
		public int DropItemID10;
		public int DropItemID11;
		public int DropItemID12;
		public int DropItemID13;
		public int DropItemID14;
		public int DropItemID15;
		public int DropItemID16;
		public int DropItemID17;
		public int DropItemID18;
		public int DropItemID19;
		public int DropItemID20;
	}

	public class DataStruct2
	{
		// Hot Data
		public int ID;
		public int Atk;
		public int Defense;

		// Cold Data
		public DropData Drop;
	}

	public class DropData
	{
		public int DropItemID1;
		public int DropItemID2;
		public int DropItemID3;
		public int DropItemID4;
		public int DropItemID5;
		public int DropItemID6;
		public int DropItemID7;
		public int DropItemID8;
		public int DropItemID9;
		public int DropItemID10;
		public int DropItemID11;
		public int DropItemID12;
		public int DropItemID13;
		public int DropItemID14;
		public int DropItemID15;
		public int DropItemID16;
		public int DropItemID17;
		public int DropItemID18;
		public int DropItemID19;
		public int DropItemID20;
	}
}
