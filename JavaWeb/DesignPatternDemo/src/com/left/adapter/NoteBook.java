package com.left.adapter;
/**
 * 适配器测试
 * @author left
 *
 */
public class NoteBook {

	private ThreePlugIf plug;

	public NoteBook(ThreePlugIf plug) {
		this.plug = plug;
	}

	public void charge() {
		plug.powerWithThree();
	}

	public static void main(String[] args) {
		GBTwoPlug two=new GBTwoPlug();
		ThreePlugIf plug = new TwoPlugAdapter(two);
		NoteBook nb = new NoteBook(plug);
		nb.charge();
	}
}
