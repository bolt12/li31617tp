package engine;

public class Revisao {
	private long revision_id;
	private String revision_timestamp;
	
	public Revisao(){
		revision_id=0;
		revision_timestamp = null;
	}
	
	public Revisao(long revision_id, String revision_timestamp) {
		this.revision_id = revision_id;
		this.revision_timestamp = revision_timestamp;
	}

	public long getRevision_id() {
		return revision_id;
	}
	public void setRevision_id(long revision_id) {
		this.revision_id = revision_id;
	}
	public String getRevision_timestamp() {
		return revision_timestamp;
	}
	public void setRevision_timestamp(String revision_timestamp) {
		this.revision_timestamp = revision_timestamp;
	}
	
	public boolean compare(Revisao revisao){
		return revisao.revision_id == this.revision_id;
	}
}
