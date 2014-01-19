// @autor witkowski01


//  Karta $JOB jest reprezentowana przez plik tekstowy i ma okreœlon¹ strukturê:	
// - WorkspaceSize: Wielkoœæ pamiêci roboczej.
// - Data: Dane do przekazania.
// - EntryPoint: Nazwa wejœciowa (tytu³). 
// - Urz¹dzenie wejœcia/wyjœcia

class SJob {
	
	private String	WorkspaceSize;
	private String 	EntryPoint;
	private String 	IODevice;
	private String  Data;
	
	public SJob (String EntryPoint, String WorkspaceSize, String IODevice, String Data){
		this.EntryPoint=EntryPoint;
		this.WorkspaceSize=WorkspaceSize;
		this.IODevice=IODevice;
		this.Data=Data;
	}
	
	public String getWorkspaceSize() {
		return WorkspaceSize;
	}


	public String getIODevice() {
		return IODevice;
	}


	public String getData() {
		return Data;
	}

	
	
}