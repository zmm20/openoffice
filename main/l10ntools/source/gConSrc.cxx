/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/
using namespace std;
#include "gConSrc.hxx"




/*****************************************************************************
 *************************   G C O N S R C . C X X   *************************
 *****************************************************************************
 * This is the conversion for .src, it uses lex to analyze
 *****************************************************************************/



/*****************************   G L O B A L S   *****************************/
convert_src_impl * convert_src::mcpImpl;



/************   I N T E R F A C E   I M P L E M E N T A T I O N   ************/
convert_src::convert_src(const string& srSourceFile, l10nMem& crMemory)
                                : convert_gen(srSourceFile, crMemory) 
                            {mcpImpl = new convert_src_impl(srSourceFile, crMemory);}
convert_src::~convert_src() {delete mcpImpl;}
void convert_src::extract() {mcpImpl->extract();}
void convert_src::insert()  {mcpImpl->insert();}



/**********************   I M P L E M E N T A T I O N   **********************/
convert_src_impl::convert_src_impl(const string& srSourceFile, l10nMem& crMemory)
                                  : convert_gen(srSourceFile, crMemory)
{
}



/**********************   I M P L E M E N T A T I O N   **********************/
convert_src_impl::~convert_src_impl()
{
}



/**********************   I M P L E M E N T A T I O N   **********************/
void convert_src_impl::extract()
{
  mbMergeMode = false;

  // run lex parser and build token tree
  runLex();
}



/**********************   I M P L E M E N T A T I O N   **********************/
void convert_src_impl::insert()
{
  mbMergeMode = true;

  // run lex parser and build token tree
  runLex();
}
