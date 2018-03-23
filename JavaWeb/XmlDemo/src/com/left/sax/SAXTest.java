package com.left.sax;

import org.xml.sax.SAXException;
import org.xml.sax.helpers.AttributesImpl;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Result;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.sax.SAXTransformerFactory;
import javax.xml.transform.sax.TransformerHandler;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

/**
 * Sax方式解析XML,也是官方提供的，基于事件驱动
 * 
 * @author left
 * 
 */
public class SAXTest {

	public static void main(String[] args) {
		new SAXTest().xmlParser();
		new SAXTest().xmlcreat();
	}

	// xml解析
	public void xmlParser() {
		SAXParserFactory factory = SAXParserFactory.newInstance();
		try {
			SAXParser parser = factory.newSAXParser();
			SaxParserHandler handler = new SaxParserHandler();
			parser.parse("XmlDemo/resources/books.xml", handler);
		} catch (ParserConfigurationException e) {
			e.printStackTrace();
		} catch (SAXException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	// 生成xml
	public void xmlcreat() {
		SAXTransformerFactory factory = (SAXTransformerFactory) SAXTransformerFactory
				.newInstance();
		try {
			TransformerHandler handler = factory.newTransformerHandler();
			Transformer transformer = handler.getTransformer();
			transformer.setOutputProperty(OutputKeys.INDENT, "yes");
			transformer.setOutputProperty(OutputKeys.ENCODING, "UTF-8");
			File file = new File("XmlDemo/resources/music.xml");
			if (!file.exists()) {
				file.createNewFile();
			}
			Result result = new StreamResult(new FileOutputStream(file));
			handler.setResult(result);
			// 必须在handler.setResult(result);之后调用
			handler.startDocument();
			AttributesImpl attributesImpl = new AttributesImpl();
			handler.startElement("", "", "musics", attributesImpl);
			for (int i = 0; i < 10; i++) {
				attributesImpl.clear();
				attributesImpl.addAttribute("", "", "id", "", i + "");
				handler.startElement("", "", "music", attributesImpl);
				for (int j = 0; j < 5; j++) {
					attributesImpl.clear();

					handler.startElement("", "", "name", attributesImpl);
					handler.characters("七里香".toCharArray(), 0, "七里香".length());
					handler.endElement("", "", "name");
				}
				handler.endElement("", "", "music");
			}

			handler.endElement("", "", "musics");

			handler.endDocument();
		} catch (TransformerConfigurationException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (SAXException e) {
			e.printStackTrace();
		}
	}

}
