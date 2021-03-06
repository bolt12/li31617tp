package engine;

import java.util.ArrayList;
import java.util.stream.Collectors;

public class Artigo implements Comparable<Artigo>
{
    private String title; 	
	private long title_ID;	
	private int n_bytes;	
	private int n_words;	
	private ArrayList<Revisao> revisions;
    
    public Artigo()
    {
    	title = " ";
    	title_ID = 0;
    	n_bytes = 0;
    	n_words = 0;
    	revisions = new ArrayList<Revisao>();
    }
    
    public Artigo(String title, long title_ID, int n_bytes, int n_words, Revisao revision){
    	this.title = title;
    	this.title_ID = title_ID;
    	this.n_bytes = n_bytes;
    	this.n_words = n_words;
    	this.revisions = new ArrayList<Revisao>();
    	this.revisions.add(revision);
    }

    public Artigo(Artigo a){
    	this.title = a.getTitle();
    	this.title_ID = a.getTitle_ID();
    	this.n_bytes = a.getN_bytes();
    	this.n_words = a.getN_words();
    	this.revisions =  a.getRevisoes();
	}

	public String getTitle() {
		return title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public long getTitle_ID() {
		return title_ID;
	}

	public void setTitle_ID(long title_ID) {
		this.title_ID = title_ID;
	}

	public int getN_bytes() {
		return n_bytes;
	}

	public void setN_bytes(int n_bytes) {
		this.n_bytes = n_bytes;
	}

	public int getN_words() {
		return n_words;
	}
	public void setN_words(int n_words) {
		this.n_words = n_words;
	}
	public void insertRevisao(Revisao revisao){
		this.revisions.add(revisao);
	}
	public ArrayList<Revisao> getRevisoes(){
	    return this.revisions.stream().map(Revisao::clone).collect(Collectors.toCollection(ArrayList::new));
	}

	@Override
	public String toString() {
		return "Artigo [title=" + title + ", title_ID=" + title_ID + "]";
	}

	public void insertOldRevisions(ArrayList<Revisao> revisoes) {
		this.revisions.addAll(revisoes);
	}

	public Revisao getNewestRevision(){
		return revisions.get(0);
	}

	public String getRevisionTimestampByID(long revision_id){
		for(Revisao revision: revisions){
			if (revision.getRevision_id() == revision_id)
				return revision.getRevision_timestamp();
		}
		return " ";
	}

	@Override
	public boolean equals(Object o) {
		if (o == this) return true;
		if (o == null || o.getClass() != this.getClass()) return false;

		Artigo a = (Artigo) o;
		return this.title.equals(a.getTitle()) && this.title_ID == a.getTitle_ID() &&
				this.n_bytes == a.getN_bytes() && this.n_words == a.getN_words() &&
				this.revisions.equals(a.getRevisoes())
				;
	}

	public int compareTo(Artigo a2){
		if(this.n_bytes<a2.getN_bytes())
			return 1;
		else if(this.n_bytes>a2.getN_bytes())
			return -1;
		else{
			if(this.title_ID<a2.getTitle_ID())
				return -1;
		}
		return 1;
	}

	public Artigo clone(){
		return new Artigo(this);
	}
}
