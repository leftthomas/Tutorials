package com.left.sax;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

/**
 * Sax方式解析时，主要是此类执行解析过程
 * 
 * @author left
 * 
 */
public class SaxParserHandler extends DefaultHandler {

	@Override
	public void startDocument() throws SAXException {
		super.startDocument();
	}

	@Override
	public void startElement(String uri, String localName, String qName,
			Attributes attributes) throws SAXException {
		super.startElement(uri, localName, qName, attributes);
		if (qName.equals("book")) {
			for (int i = 0; i < attributes.getLength(); i++) {
				System.out.println(attributes.getQName(i) + ":"
						+ attributes.getValue(i));
			}
		} else if (!qName.equals("bookstore") && !qName.equals("book")) {
				System.out.print(qName+":");
		}
	}

	@Override
	public void characters(char[] ch, int start, int length)
			throws SAXException {
		super.characters(ch, start, length);
		String value = new String(ch, start, length);
		if (!value.trim().equals(""))
			System.out.println(value);
	}

	@Override
	public void endElement(String uri, String localName, String qName)
			throws SAXException {
		super.endElement(uri, localName, qName);
		if (qName.equals("book")) {
			// 解析完一本书，换行
			System.out.println("");
		}
	}

	@Override
	public void endDocument() throws SAXException {
		super.endDocument();
	}
}
