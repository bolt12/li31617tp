package engine;

public class Contribuidor
{
    
	private String contributor_name;		
	private long contributor_id;		
	private int contributions_number;	
	
	public Contribuidor()
    {
		contributor_name = null;
		contributor_id = 0;
		contributions_number = 0;
    }
    
	public Contribuidor(String contributor_name, long contributor_id, int contributions_number){
		this.contributor_name = contributor_name;
		this.contributor_id = contributor_id;
		this.contributions_number = contributions_number;
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

}
