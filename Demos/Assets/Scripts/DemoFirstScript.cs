﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DemoFirstScript: NewtonBodyScript
{

	// Use this for initialization
	void Start ()
    {
		
	}
	
	// Update is called once per frame
	void Update ()
    {
		
	}

    override public void OnCollision(NewtonBody otherBody)
    {
        //Debug.Log("xxxxxx woohoo collision notification script !!");
        if (GetComponent<NewtonCollider>().m_isTrigger)
        {
            Debug.Log(gameObject.name + " is trigger");
        }
        //Debug.Log(this.gameObject.name + " colliding with " + otherBody.gameObject.name);    
    }

}
