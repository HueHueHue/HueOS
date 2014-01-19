// @autor witkowski01


//  Karta $JOB jest reprezentowana przez plik tekstowy i ma okre�lon� struktur�:	
// - WorkspaceSize: Wielko�� pami�ci roboczej.
// - Data: Dane do przekazania.
// - EntryPoint: Nazwa wej�ciowa (tytu�). 
// - Urz�dzenie wej�cia/wyj�cia

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