package engine;

import java.util.ArrayList;

public class Artigo
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
		return this.revisions;
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
}
