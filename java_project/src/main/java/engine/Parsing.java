package engine;

import java.io.FileInputStream;
import java.io.FileNotFoundException;

import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;

public class Parsing {
	
	public Parsing(){
		
	}
	
	public void parseText(String s, Artigo artigo){

	    int wordCount = 0;

	    boolean word = false;
	    int endOfText = s.length() - 1;

	    for (int i = 0; i < s.length(); i++) {
	        // Se estivermos numa letra, word = true.
	        if (Character.isLetter(s.charAt(i)) && i != endOfText) {
	            word = true;
	            // Se não estivermos numa letra mas viermos de uma letra,
	            // acrescentamos ao contador.
	        } else if (!Character.isLetter(s.charAt(i)) && word) {
	            wordCount++;
	            word = false;
	            // Se o ultimo caracter for uma letra
	        } else if (Character.isLetter(s.charAt(i)) && i == endOfText) {
	            wordCount++;
	        }
	    }
	    artigo.setN_bytes(s.length()*2);
	    artigo.setN_words(wordCount);
	}
	
	public void parseContribuidor(XMLStreamReader stream, Contribuidor contribuidor) throws XMLStreamException{
		
		stream.next();
		 while(!(stream.isEndElement() && stream.getName().getLocalPart().equals("contributor"))){
			 if(stream.isStartElement() && stream.getName().getLocalPart().equals("username")){
				 stream.next();
				 contribuidor.setContributor_name(stream.getText());
			 }
			 else if(stream.isStartElement() && stream.getName().getLocalPart().equals("id")){
				 stream.next();
				 contribuidor.setContributor_id(Long.parseLong(stream.getText()));
			 }
			 else if(stream.isStartElement() && stream.getName().getLocalPart().equals("ip")){
				 contribuidor.setIsIP(true);
			 }
			 
			 stream.next();
		 }
	}
	
	public void parseRevision(XMLStreamReader stream, Artigo artigo, Contribuidor contribuidor) throws XMLStreamException{
		Revisao revisao = new Revisao();
		 stream.next();
		 
		 while(!(stream.isEndElement() && stream.getName().getLocalPart().equals("revision"))){
			 //Este ciclo corre enquanto não for encontrada a closing tag de revision
			 
			 if(stream.isStartElement() && stream.getName().getLocalPart().equals("id")){
				 stream.next();
				 revisao.setRevision_id(Long.parseLong(stream.getText()));
			 }
			 else if (stream.isStartElement() && stream.getName().getLocalPart().equals("timestamp")){
				 stream.next();
				 revisao.setRevision_timestamp(stream.getText());
			 }
			 else if (stream.isStartElement() && stream.getName().getLocalPart().equals("text")){
				 stream.next();
				 parseText(stream.getText(),artigo);
			 }
			 else if (stream.isStartElement() && stream.getName().getLocalPart().equals("contributor")){
				 // Parse do Contribuidor
				 
				 parseContribuidor(stream, contribuidor);
			 } 
			 stream.next();
		 }
		 
		 artigo.insertRevisao(revisao);
		
	}
	
	public void parsePage(XMLStreamReader stream, Artigo artigo, Contribuidor contribuidor) throws XMLStreamException{
		
		stream.nextTag();
		 
		 while(!(stream.isEndElement() && stream.getName().getLocalPart().equals("page"))){
			 //Este ciclo corre enquanto não for encontrado o End element de page
			 if(stream.isStartElement() && stream.getName().getLocalPart().equals("title")){
				 stream.next();
				 artigo.setTitle(stream.getText());
			 }
			 else if (stream.isStartElement() && stream.getName().getLocalPart().equals("id")){
				 stream.next();
				 artigo.setTitle_ID(Long.parseLong(stream.getText()));
			 }
			 else if (stream.isStartElement() && stream.getName().getLocalPart().equals("revision")){
				 // Parse da tag Revision
				 
				 parseRevision(stream, artigo, contribuidor);
			 }
			 stream.next();
		 }
	}

	public void openXML(String fileName, Estruturas database){
		XMLInputFactory factory = XMLInputFactory.newInstance();
		try{
			XMLStreamReader stream = factory.createXMLStreamReader(new FileInputStream(fileName));
			while(stream.hasNext()){
				stream.next();
				if(stream.isStartElement() && stream.getName().getLocalPart().equals("page")){
						 
						 Artigo artigo = new Artigo();
						 Contribuidor contribuidor = new Contribuidor();
						 
						 parsePage(stream, artigo, contribuidor);
						 
						 //System.out.println(artigo.toString());
						 //System.out.println(contribuidor.toString());
						 database.addInfo(artigo, contribuidor);
						 
				}
			}
	
		} catch (FileNotFoundException | XMLStreamException e) {
	            e.printStackTrace();
		}
	}
}