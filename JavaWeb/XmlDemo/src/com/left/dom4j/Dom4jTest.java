package com.left.dom4j;

import org.dom4j.*;
import org.dom4j.io.OutputFormat;
import org.dom4j.io.SAXReader;
import org.dom4j.io.XMLWriter;

import java.io.*;
import java.util.Iterator;
import java.util.List;

/**
 * Dom4j方式解析xml,需要dom4j jar，，基于底层API.性能最佳，推荐使用
 * 
 * @author left
 * 
 */
public class Dom4jTest {

	public static void main(String[] args) {
		new Dom4jTest().xmlParser();
		new Dom4jTest().rsscreat();
		;
	}

	// xml解析
	@SuppressWarnings("unchecked")
	public void xmlParser() {
		SAXReader reader = new SAXReader();
		try {
			Document document = reader.read(new File("XmlDemo/resources/books.xml"));
			Element rootElement = document.getRootElement();
			Iterator<?> iterator = rootElement.elementIterator();
			while (iterator.hasNext()) {
				Element book = (Element) iterator.next();
				List<Attribute> attributes = book.attributes();
				for (Attribute attribute : attributes) {
					System.out.println(attribute.getName() + ":"
							+ attribute.getValue());
				}
				Iterator<?> it = book.elementIterator();
				while (it.hasNext()) {
					Element element = (Element) it.next();
					System.out.println(element.getName() + ":"
							+ element.getTextTrim());
				}
				// 解析完一本书换行
				System.out.println("");
			}
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	// 生成rss
	public void rsscreat() {
		Document document=DocumentHelper.createDocument();
		Element rss=document.addElement("rss");
		rss.addAttribute("version", "2.0");
		Element channel=rss.addElement("channel");
		Element title=channel.addElement("title");
		title.setText("国内新闻");
		OutputFormat format=OutputFormat.createPrettyPrint();
		File file = new File("XmlDemo/resources/rss.xml");
		try {
			XMLWriter writer=new XMLWriter(new FileOutputStream(file),format);
			writer.write(document);
			writer.close();
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
