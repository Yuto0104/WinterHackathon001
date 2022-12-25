xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 53;
 0.00000;0.49985;-0.79022;,
 -4.59352;1.14385;-0.61766;,
 -4.59352;2.56429;-3.65548;,
 0.00000;2.39379;-4.84064;,
 -4.59352;4.28439;-4.61054;,
 0.00000;4.68725;-6.11405;,
 -4.59352;5.29650;-2.92339;,
 -0.00002;6.03674;-3.86452;,
 -4.59351;5.00774;0.41766;,
 -0.00001;5.65173;0.59022;,
 -4.59352;3.58728;3.45548;,
 0.00001;3.75779;4.64064;,
 -4.59352;1.86719;4.41054;,
 0.00000;1.46433;5.91406;,
 -4.59352;0.85508;2.72339;,
 0.00000;0.11484;3.66452;,
 -4.59352;1.14385;-0.61766;,
 0.00000;0.49985;-0.79022;,
 -12.09144;1.52941;0.51928;,
 -12.79547;2.45149;-1.41302;,
 -13.08711;3.58790;-2.01124;,
 -12.79547;4.27296;-0.92496;,
 -12.09144;4.10535;1.20950;,
 -11.38738;3.18328;3.14181;,
 -11.09576;2.04686;3.74003;,
 -11.38738;1.36180;2.65374;,
 -12.09144;1.52941;0.51928;,
 -16.43407;1.68148;2.52769;,
 -17.19181;2.09148;1.75200;,
 -17.50562;2.63855;1.53179;,
 -17.19181;3.00222;1.99603;,
 -16.43407;2.96945;2.87280;,
 -15.67637;2.55944;3.64847;,
 -15.36250;2.01238;3.86869;,
 -15.67637;1.64871;3.40445;,
 -16.43407;1.68148;2.52769;,
 -20.00390;1.64152;5.25278;,
 -20.00390;1.64152;5.25278;,
 -20.00390;1.64152;5.25278;,
 -20.00390;1.64152;5.25278;,
 -20.00390;1.64152;5.25278;,
 -20.00390;1.64152;5.25278;,
 -20.00390;1.64152;5.25278;,
 -20.00390;1.64152;5.25278;,
 0.00000;3.07579;-0.10000;,
 0.00000;0.49985;-0.79022;,
 0.00000;2.39379;-4.84064;,
 0.00000;4.68725;-6.11405;,
 -0.00002;6.03674;-3.86452;,
 -0.00001;5.65173;0.59022;,
 0.00001;3.75779;4.64064;,
 0.00000;1.46433;5.91406;,
 0.00000;0.11484;3.66452;;
 
 40;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;1,18,19,2;,
 4;2,19,20,4;,
 4;4,20,21,6;,
 4;6,21,22,8;,
 4;8,22,23,10;,
 4;10,23,24,12;,
 4;12,24,25,14;,
 4;14,25,26,16;,
 4;18,27,28,19;,
 4;19,28,29,20;,
 4;20,29,30,21;,
 4;21,30,31,22;,
 4;22,31,32,23;,
 4;23,32,33,24;,
 4;24,33,34,25;,
 4;25,34,35,26;,
 3;27,36,28;,
 3;28,37,29;,
 3;29,38,30;,
 3;30,39,31;,
 3;31,40,32;,
 3;32,41,33;,
 3;33,42,34;,
 3;34,43,35;,
 3;44,45,46;,
 3;44,46,47;,
 3;44,47,48;,
 3;44,48,49;,
 3;44,49,50;,
 3;44,50,51;,
 3;44,51,52;,
 3;44,52,45;;
 
 MeshMaterialList {
  5;
  40;
  4,
  4,
  1,
  1,
  1,
  1,
  4,
  4,
  4,
  4,
  1,
  1,
  1,
  1,
  4,
  4,
  4,
  4,
  1,
  1,
  1,
  1,
  4,
  4,
  4,
  4,
  1,
  1,
  1,
  1,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.194510;0.304314;0.461176;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\3D表\現技術(後期)\\作品\\Ver.1.1(試作3号)\\data\\TEXTURE\\口.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  50;
  -0.143636;-0.955910;-0.256135;,
  -0.198603;-0.718693;-0.666361;,
  -0.236668;-0.471638;-0.849439;,
  -0.198602;0.955587;-0.217740;,
  -0.143635;0.955910;0.256135;,
  -0.198603;0.718693;0.666361;,
  -0.236668;0.471640;0.849438;,
  -0.198603;-0.955587;0.217738;,
  -0.115080;-0.961193;-0.250727;,
  -0.184905;-0.725190;-0.663257;,
  -0.229444;-0.478751;-0.847439;,
  -0.184905;0.959661;-0.211803;,
  -0.115080;0.957781;0.263461;,
  -0.136144;0.719877;0.680619;,
  -0.154992;0.471279;0.868259;,
  -0.136144;-0.963741;0.229494;,
  -0.103644;-0.970388;-0.218184;,
  -0.256864;-0.748662;-0.611167;,
  -0.347691;-0.510068;-0.786728;,
  -0.256865;0.953944;-0.154955;,
  -0.103644;0.949473;0.296242;,
  -0.041829;0.705024;0.707948;,
  -0.017830;0.451739;0.891972;,
  -0.041828;-0.964544;0.260588;,
  -0.116272;-0.977513;-0.175924;,
  -0.384024;-0.775450;-0.501201;,
  -0.537681;-0.550405;-0.638712;,
  -0.384023;0.922160;-0.046328;,
  -0.116272;0.934512;0.336403;,
  0.049271;0.700648;0.711804;,
  0.127731;0.453912;0.881844;,
  0.049271;-0.962681;0.266116;,
  -0.296464;-0.901617;-0.314955;,
  1.000000;0.000002;-0.000000;,
  -0.236667;0.833171;-0.499815;,
  -0.229444;0.838331;-0.494528;,
  -0.236667;-0.833170;0.499816;,
  -0.154992;-0.842269;0.516295;,
  -0.347690;0.835097;-0.426291;,
  -0.017830;-0.837203;0.546601;,
  -0.537678;0.796024;-0.277934;,
  0.127733;-0.834018;0.536748;,
  -0.177470;0.901096;0.395638;,
  0.217687;-0.834354;0.506425;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000004;0.000001;,
  1.000000;0.000006;0.000001;,
  1.000000;0.000005;-0.000001;,
  1.000000;0.000001;-0.000001;,
  1.000000;-0.000002;-0.000000;;
  40;
  4;0,8,9,1;,
  4;1,9,10,2;,
  4;34,35,11,3;,
  4;3,11,12,4;,
  4;4,12,13,5;,
  4;5,13,14,6;,
  4;36,37,15,7;,
  4;7,15,8,0;,
  4;8,16,17,9;,
  4;9,17,18,10;,
  4;35,38,19,11;,
  4;11,19,20,12;,
  4;12,20,21,13;,
  4;13,21,22,14;,
  4;37,39,23,15;,
  4;15,23,16,8;,
  4;16,24,25,17;,
  4;17,25,26,18;,
  4;38,40,27,19;,
  4;19,27,28,20;,
  4;20,28,29,21;,
  4;21,29,30,22;,
  4;39,41,31,23;,
  4;23,31,24,16;,
  3;24,32,25;,
  3;25,32,26;,
  3;40,42,27;,
  3;27,42,28;,
  3;28,42,29;,
  3;29,42,30;,
  3;41,43,31;,
  3;31,32,24;,
  3;33,44,44;,
  3;33,44,45;,
  3;33,45,46;,
  3;33,46,47;,
  3;33,47,48;,
  3;33,48,49;,
  3;33,49,44;,
  3;33,44,44;;
 }
 MeshTextureCoords {
  53;
  0.000000;1.000000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.125000;1.000000;,
  0.250000;0.750000;,
  0.250000;1.000000;,
  0.375000;0.750000;,
  0.375000;1.000000;,
  0.500000;0.750000;,
  0.500000;1.000000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.750000;0.750000;,
  0.750000;1.000000;,
  0.875000;0.750000;,
  0.875000;1.000000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
