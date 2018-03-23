package com.left.jdom;

import org.jdom2.Attribute;
import org.jdom2.Document;
import org.jdom2.Element;
import org.jdom2.JDOMException;
import org.jdom2.input.SAXBuilder;
import org.jdom2.output.Format;
import org.jdom2.output.XMLOutputter;

import java.io.*;
import java.util.List;

/**
 * JDOM方式对XML解析，需要jdom jar包
 * 
 * @author left
 * 
 */
public class JDOMTest {

	public static void main(String[] args) {
		new JDOMTest().xmlcreat();
		new JDOMTest().xmlParser();
	}

	// xml解析
	public void xmlParser() {
		SAXBuilder builder = new SAXBuilder();
		try {
			InputStream stream = new FileInputStream("XmlDemo/resources/books.xml");
			Document document = builder.build(stream);
			Element rootelement = document.getRootElement();
			List<Element> elements = rootelement.getChildren();
			for (Element element : elements) {

				List<Attribute> attributes = element.getAttributes();
				for (Attribute attribute : attributes) {
					System.out.println(attribute.getName() + ":"
							+ attribute.getValue());
				}
				List<Element> childs = element.getChildren();
				for (Element child : childs) {
					System.out
							.println(child.getName() + ":" + child.getValue());
				}
				// 换行解析另一个节点
				System.out.println("");
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (JDOMException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	// 生成rss
	public void xmlcreat() {
		Element rss=new Element("rss");
		rss.setAttribute("version", "2.0");
		Document document=new Document(rss);
		Element channel=new Element("channel");
		rss.addContent(channel);
		Element title=new Element("title");
		title.setText("晚间新闻");
		channel.addContent(title);
		Format format=Format.getCompactFormat();
		format.setIndent("");
		format.setEncoding("UTF-8");
		XMLOutputter outputter=new XMLOutputter(format);
		try {
			outputter.output(document, new FileOutputStream(new File("XmlDemo/resources/rss2.xml")));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
