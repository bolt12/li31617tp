package engine;

public class Contribuidor implements Comparable<Contribuidor>
{
    private boolean isIP;
	private String contributor_name;		
	private long contributor_id;		
	private int contributions_number;	
	
	public Contribuidor()
    {
		isIP = false;
		contributor_name = " ";
		contributor_id = 0;
		contributions_number = 1;
    }
    
	public Contribuidor(String contributor_name, long contributor_id, int contributions_number){
		this.contributor_name = contributor_name;
		this.contributor_id = contributor_id;
		this.contributions_number = contributions_number;
	}

	public Contribuidor(Contribuidor c){
		this.isIP = c.isIP();
		this.contributor_name = c.getContributor_name();
		this.contributor_id = c.getContributor_id();
		this.contributions_number = c.getContributions_number();
	}

    public String getContributor_name() {
		return contributor_name;
	}

	public void setContributor_name(String contributor_name) {
		this.contributor_name = contributor_name;
	}

	public long getContributor_id() {
		return contributor_id;
	}

	public void setContributor_id(long contributor_id) {
		this.contributor_id = contributor_id;
	}

	public int getContributions_number() {
		return contributions_number;
	}

	public void setContributions_number(int contributions_number) {
		this.contributions_number = contributions_number;
	}

	public void addContributions_number(){
		this.contributions_number += 1;
	}

	public boolean isIP() {
		return isIP;
	}

	public void setIsIP(boolean isIP) {
		this.isIP = isIP;
	}

	public int compareTo(Contribuidor c2){
		if(this.getContributions_number()<c2.getContributions_number())
			return 1;
		if(this.getContributions_number()>c2.getContributions_number())
			return -1;
		else{
			if(this.getContributor_id()<c2.getContributor_id())
				return -1;
		}
		return 1;
	}

	@Override
	public boolean equals(Object o) {
		if (o == this) return true;
		if (o == null || o.getClass() != this.getClass()) return false;
		Contribuidor c = (Contribuidor) o;
		return this.contributor_name.equals(c.contributor_name) && this.contributor_id == c.getContributor_id()
				&& this.contributions_number == c.getContributions_number();
	}

	@Override
	public String toString() {
		return "Contribuidor [isIP=" + isIP + ", contributor_name=" + contributor_name + ", contributor_id="
				+ contributor_id + ", contributions_number=" + contributions_number + "]";
	}

	public Contribuidor clone(){
		return new Contribuidor(this);
	}

}
