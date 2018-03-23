package com.left.dom;

import org.w3c.dom.*;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import java.io.IOException;

/**
 * DOM方式,w3c官方提供的方法，基于tree,但是内存占用多，可能会溢出，不建议使用
 * 
 * @author left
 * 
 */
public class DOMTest {

	public static void main(String[] args) {
		new DOMTest().xmlcreat();
		new DOMTest().xmlParser();
	}

	// xml解析
	public void xmlParser() {
		DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder db = dbf.newDocumentBuilder();
			Document document = db.parse("XmlDemo/resources/books.xml");
			NodeList booklist = document.getElementsByTagName("book");
			for (int i = 0; i < booklist.getLength(); i++) {
				Node book = booklist.item(i);
				// book节点的属性列表
				NamedNodeMap attributesMap = book.getAttributes();
				for (int j = 0; j < attributesMap.getLength(); j++) {
					System.out.println(attributesMap.item(j).getNodeName()
							+ ":" + attributesMap.item(j).getNodeValue());
				}
				// book节点的子节点
				NodeList list = book.getChildNodes();
				// 注意总节点数，换行符和空白也是一个节点
				for (int k = 0; k < list.getLength(); k++) {
					// 只获取Element类型的节点，即去除空白和换行
					if (list.item(k).getNodeType() == Node.ELEMENT_NODE) {
						// 直接通过list.item(k).getNodeValue()是获取不到值的,为null，必须list.item(k).getFirstChild().getNodeValue()这样获取
						System.out.println(list.item(k).getNodeName() + ":"
								+ list.item(k).getFirstChild().getNodeValue());
						// 或者这样获取，注意区别在于此子节点下是否还有子节点
						System.out.println(list.item(k).getNodeName() + ":"
								+ list.item(k).getTextContent());
					}
				}
				// 换行
				System.out.println("");
			}
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
		DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder db = dbf.newDocumentBuilder();
			Document document = db.newDocument();
			document.setXmlStandalone(true);
			Element movies=document.createElement("movies");
			Element movie=document.createElement("movie");
			Element name=document.createElement("name");
			name.setTextContent("阿凡达");
			movie.appendChild(name);
			movie.setAttribute("id", "1");
			movies.appendChild(movie);
			document.appendChild(movies);
			TransformerFactory factory=TransformerFactory.newInstance();
			Transformer transformer=factory.newTransformer();
			transformer.setOutputProperty(OutputKeys.INDENT, "yes");
			transformer.transform(new DOMSource(document), new StreamResult(new File("XmlDemo/resources/movies.xml")));
		} catch (ParserConfigurationException e) {
			e.printStackTrace();
		} catch (TransformerConfigurationException e) {
			e.printStackTrace();
		} catch (TransformerException e) {
			e.printStackTrace();
		}
	}
}
