package com.left.adapter;

/**
 * 二相转三相的插座适配器
 * 
 * @author left
 * 
 */
public class TwoPlugAdapter implements ThreePlugIf {
	private GBTwoPlug plug;

	public TwoPlugAdapter(GBTwoPlug plug) {
		this.plug = plug;
	}

	public void powerWithThree() {
		plug.powerWithTwo();
	}

}
