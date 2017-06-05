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

	public Revisao(Revisao r){
		this.revision_id = r.getRevision_id();
		this.revision_timestamp = r.getRevision_timestamp();
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

	@Override
	public boolean equals(Object o) {
		if (o == this) return true;
		if (o == null || o.getClass() != this.getClass()) return false;
		Revisao r = (Revisao) o;
		return this.revision_id == r.revision_id && this.revision_timestamp.equals(r.getRevision_timestamp());
	}

	public Revisao clone(){
		return new Revisao(this);
	}
}
