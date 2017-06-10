package engine;

import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class Parsing {
		
	public Parsing(){
	}
	
	private static byte[] getBytesFast(String str) {
        final char buffer[] = new char[str.length()];
        final int length = str.length();
        str.getChars(0, length, buffer, 0);
        final byte b[] = new byte[length];
        for (int j = 0; j < length; j++)
            b[j] = (byte) buffer[j];
        return b;
    }
	private void parseText(String s, Artigo artigo){

		int wordCount = 0;
		int length = s.length();
		
		boolean word = false;
		int endOfText = s.length() - 1;

		for (int i = 0; i < length; i++) {
			// Se estivermos numa letra, word = true.
			if (!Character.isWhitespace(s.charAt(i)) && i != endOfText) {
				word = true;
				// Se não estivermos numa letra mas viermos de uma letra,
				// acrescentamos ao contador.
			} else if (Character.isWhitespace(s.charAt(i)) && word) {
				wordCount++;
				word = false;
				// Se o ultimo caracter for uma letra
			} else if (!Character.isWhitespace(s.charAt(i)) && i == endOfText) {
				wordCount++;
			}
		}
		artigo.setN_bytes(getBytesFast(s).length);
	    artigo.setN_words(wordCount);

	}
		
	private void parseContribuidor(XMLStreamReader stream, Contribuidor contribuidor) throws XMLStreamException{
		
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
	
	private void parseRevision(XMLStreamReader stream, Artigo artigo, Contribuidor contribuidor) throws XMLStreamException{
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
				 parseText(stream.getText(), artigo);
				 
			 }
			 else if (stream.isStartElement() && stream.getName().getLocalPart().equals("contributor")){
				 // Parse do Contribuidor
				 
				 parseContribuidor(stream, contribuidor);
			 } 
			 stream.next();
		 }
		 
		 artigo.insertRevisao(revisao);
		
	}

	private void parsePage(XMLStreamReader stream, Artigo artigo, Contribuidor contribuidor) throws XMLStreamException{
		
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
		factory.setProperty(XMLInputFactory.IS_COALESCING, true);
		try{
			XMLStreamReader stream = factory.createXMLStreamReader(new FileInputStream(fileName));
			while(stream.hasNext()){
				stream.next();
				if(stream.isStartElement() && stream.getName().getLocalPart().equals("page")){
						 
						 Artigo artigo = new Artigo();
						 Contribuidor contribuidor = new Contribuidor();
						 
						 parsePage(stream, artigo, contribuidor);
						 
						 database.addInfo(artigo, contribuidor);
						 

				}
			}
			
			
		} catch (FileNotFoundException | XMLStreamException e) {
	            e.printStackTrace();
		}
	}
}