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
 258;
 -2.91898;5.54160;17.38802;,
 4.15535;5.54160;17.38802;,
 4.15535;5.54160;-15.91042;,
 -2.91898;5.54160;-15.91042;,
 -2.91898;5.09143;-16.72948;,
 4.15535;5.09143;-16.72948;,
 4.15535;4.90209;-16.72948;,
 -2.91898;4.90209;-16.72948;,
 -2.91898;4.45192;-15.91042;,
 4.15535;4.45192;-15.91042;,
 4.15535;4.45192;17.38802;,
 -2.91898;4.45192;17.38802;,
 -2.91898;4.90209;18.20707;,
 4.15535;4.90209;18.20707;,
 4.15535;5.09143;18.20707;,
 -2.91898;5.09143;18.20707;,
 4.70492;5.09143;17.38802;,
 4.70492;4.90209;17.38802;,
 4.70492;4.90209;-15.91042;,
 4.70492;5.09143;-15.91042;,
 -3.46855;4.90209;17.38802;,
 -3.46855;5.09143;17.38802;,
 -3.46855;5.09143;-15.91042;,
 -3.46855;4.90209;-15.91042;,
 -2.91898;5.54160;-15.91042;,
 4.15535;5.54160;-15.91042;,
 4.15535;5.50733;-16.22386;,
 -2.91898;5.50733;-16.22386;,
 4.15535;5.40975;-16.48956;,
 -2.91898;5.40975;-16.48956;,
 4.15535;5.26370;-16.66712;,
 -2.91898;5.26370;-16.66712;,
 4.15535;5.09143;-16.72948;,
 -2.91898;4.48618;-16.22386;,
 4.15535;4.48618;-16.22386;,
 4.15535;4.45192;-15.91042;,
 -2.91898;4.58377;-16.48956;,
 4.15535;4.58377;-16.48956;,
 -2.91898;4.72982;-16.66712;,
 4.15535;4.72982;-16.66712;,
 -2.91898;4.90209;-16.72948;,
 4.15535;4.90209;-16.72948;,
 -2.91898;5.50733;17.70145;,
 4.15535;5.50733;17.70145;,
 4.15535;5.54160;17.38802;,
 -2.91898;5.40975;17.96716;,
 4.15535;5.40975;17.96716;,
 -2.91898;5.26370;18.14472;,
 4.15535;5.26370;18.14472;,
 -2.91898;5.09143;18.20707;,
 4.15535;5.09143;18.20707;,
 -2.91898;4.45192;17.38802;,
 4.15535;4.45192;17.38802;,
 4.15535;4.48618;17.70145;,
 -2.91898;4.48618;17.70145;,
 4.15535;4.58377;17.96716;,
 -2.91898;4.58377;17.96716;,
 4.15535;4.72982;18.14472;,
 -2.91898;4.72982;18.14472;,
 4.15535;4.90209;18.20707;,
 4.36566;5.50733;17.38802;,
 4.36566;5.50733;-15.91042;,
 4.54395;5.40975;17.38802;,
 4.54395;5.40975;-15.91042;,
 4.66308;5.26370;17.38802;,
 4.66308;5.26370;-15.91042;,
 4.70492;5.09143;-15.91042;,
 4.36566;4.48618;-15.91042;,
 4.36566;4.48618;17.38802;,
 4.54395;4.58377;-15.91042;,
 4.54395;4.58377;17.38802;,
 4.66308;4.72982;-15.91042;,
 4.66308;4.72982;17.38802;,
 4.70492;4.90209;-15.91042;,
 4.70492;4.90209;17.38802;,
 -3.12928;5.50733;-15.91042;,
 -3.12928;5.50733;17.38802;,
 -3.30758;5.40975;-15.91042;,
 -3.30758;5.40975;17.38802;,
 -3.42671;5.26370;-15.91042;,
 -3.42671;5.26370;17.38802;,
 -3.46855;5.09143;-15.91042;,
 -3.46855;5.09143;17.38802;,
 -3.12928;4.48618;17.38802;,
 -3.12928;4.48618;-15.91042;,
 -3.30758;4.58377;17.38802;,
 -3.30758;4.58377;-15.91042;,
 -3.42671;4.72982;17.38802;,
 -3.42671;4.72982;-15.91042;,
 -3.46855;4.90209;-15.91042;,
 4.36566;5.09143;-16.66712;,
 4.36566;4.90209;-16.66712;,
 4.54395;5.09143;-16.48956;,
 4.54395;4.90209;-16.48956;,
 4.66308;5.09143;-16.22386;,
 4.66308;4.90209;-16.22386;,
 4.36566;4.90209;18.14472;,
 4.36566;5.09143;18.14472;,
 4.54395;4.90209;17.96716;,
 4.54395;5.09143;17.96716;,
 4.66308;4.90209;17.70145;,
 4.66308;5.09143;17.70145;,
 -3.12928;4.90209;-16.66712;,
 -3.12928;5.09143;-16.66712;,
 -3.30758;4.90209;-16.48956;,
 -3.30758;5.09143;-16.48956;,
 -3.42671;4.90209;-16.22386;,
 -3.42671;5.09143;-16.22386;,
 -3.12928;5.09143;18.14472;,
 -3.12928;4.90209;18.14472;,
 -3.30758;5.09143;17.96716;,
 -3.30758;4.90209;17.96716;,
 -3.42671;5.09143;17.70145;,
 -3.42671;4.90209;17.70145;,
 4.43013;5.40975;-16.31994;,
 4.59506;5.26370;-16.28877;,
 4.40922;5.26370;-16.56572;,
 -3.19376;5.40975;-16.31994;,
 -3.35869;5.26370;-16.28877;,
 -3.17285;5.26370;-16.56572;,
 4.43013;4.58377;-16.31994;,
 4.59506;4.72982;-16.28877;,
 4.40922;4.72982;-16.56572;,
 4.43013;5.40975;17.79754;,
 4.59506;5.26370;17.76638;,
 4.40922;5.26370;18.04332;,
 -3.19376;4.58377;-16.31994;,
 -3.35869;4.72982;-16.28877;,
 -3.17285;4.72982;-16.56572;,
 4.43013;4.58377;17.79754;,
 4.59506;4.72982;17.76638;,
 4.40922;4.72982;18.04332;,
 -3.19376;5.40975;17.79754;,
 -3.35869;5.26370;17.76638;,
 -3.17285;5.26370;18.04332;,
 -3.19376;4.58377;17.79754;,
 -3.35869;4.72982;17.76638;,
 -3.17285;4.72982;18.04332;,
 2.34885;4.95098;15.38176;,
 2.87644;4.95098;15.38176;,
 2.87644;-0.64865;15.38176;,
 2.34885;-0.64865;15.38176;,
 2.87644;4.95098;15.38176;,
 2.87644;4.95098;16.16803;,
 2.87644;-0.64865;16.16803;,
 2.87644;-0.64865;15.38176;,
 2.87644;4.95098;16.16803;,
 2.34885;4.95098;16.16803;,
 2.34885;-0.64865;16.16803;,
 2.87644;-0.64865;16.16803;,
 2.34885;4.95098;16.16803;,
 2.34885;4.95098;15.38176;,
 2.34885;-0.64865;15.38176;,
 2.34885;-0.64865;16.16803;,
 2.87644;4.95098;15.38176;,
 2.34885;4.95098;15.38176;,
 2.34885;-0.64865;15.38176;,
 2.87644;-0.64865;15.38176;,
 -2.34885;-0.64865;15.38176;,
 -2.87644;-0.64865;15.38176;,
 -2.87644;4.95098;15.38176;,
 -2.34885;4.95098;15.38176;,
 -2.87644;-0.64865;15.38176;,
 -2.87644;-0.64865;16.16803;,
 -2.87644;4.95098;16.16803;,
 -2.87644;4.95098;15.38176;,
 -2.87644;-0.64865;16.16803;,
 -2.34885;-0.64865;16.16803;,
 -2.34885;4.95098;16.16803;,
 -2.87644;4.95098;16.16803;,
 -2.34885;-0.64865;16.16803;,
 -2.34885;-0.64865;15.38176;,
 -2.34885;4.95098;15.38176;,
 -2.34885;4.95098;16.16803;,
 -2.34885;4.95098;15.38176;,
 -2.87644;4.95098;15.38176;,
 -2.87644;-0.64865;15.38176;,
 -2.34885;-0.64865;15.38176;,
 2.34885;-0.64865;-15.38176;,
 2.87644;-0.64865;-15.38176;,
 2.87644;4.95098;-15.38176;,
 2.34885;4.95098;-15.38176;,
 2.87644;-0.64865;-15.38176;,
 2.87644;-0.64865;-16.16803;,
 2.87644;4.95098;-16.16803;,
 2.87644;4.95098;-15.38176;,
 2.87644;-0.64865;-16.16803;,
 2.34885;-0.64865;-16.16803;,
 2.34885;4.95098;-16.16803;,
 2.87644;4.95098;-16.16803;,
 2.34885;-0.64865;-16.16803;,
 2.34885;-0.64865;-15.38176;,
 2.34885;4.95098;-15.38176;,
 2.34885;4.95098;-16.16803;,
 2.34885;4.95098;-15.38176;,
 2.87644;4.95098;-15.38176;,
 2.87644;-0.64865;-15.38176;,
 2.34885;-0.64865;-15.38176;,
 -2.34885;4.95098;-15.38176;,
 -2.87644;4.95098;-15.38176;,
 -2.87644;-0.64865;-15.38176;,
 -2.34885;-0.64865;-15.38176;,
 -2.87644;4.95098;-15.38176;,
 -2.87644;4.95098;-16.16803;,
 -2.87644;-0.64865;-16.16803;,
 -2.87644;-0.64865;-15.38176;,
 -2.87644;4.95098;-16.16803;,
 -2.34885;4.95098;-16.16803;,
 -2.34885;-0.64865;-16.16803;,
 -2.87644;-0.64865;-16.16803;,
 -2.34885;4.95098;-16.16803;,
 -2.34885;4.95098;-15.38176;,
 -2.34885;-0.64865;-15.38176;,
 -2.34885;-0.64865;-16.16803;,
 -2.87644;4.95098;-15.38176;,
 -2.34885;4.95098;-15.38176;,
 -2.34885;-0.64865;-15.38176;,
 -2.87644;-0.64865;-15.38176;,
 2.31157;5.29671;0.02855;,
 2.83915;5.29671;0.02855;,
 2.83915;-0.30292;0.02855;,
 2.31157;-0.30292;0.02855;,
 2.83915;5.29671;0.02855;,
 2.83915;5.29671;0.81482;,
 2.83915;-0.30292;0.81482;,
 2.83915;-0.30292;0.02855;,
 2.83915;5.29671;0.81482;,
 2.31157;5.29671;0.81482;,
 2.31157;-0.30292;0.81482;,
 2.83915;-0.30292;0.81482;,
 2.31157;5.29671;0.81482;,
 2.31157;5.29671;0.02855;,
 2.31157;-0.30292;0.02855;,
 2.31157;-0.30292;0.81482;,
 2.83915;5.29671;0.02855;,
 2.31157;5.29671;0.02855;,
 2.31157;-0.30292;0.02855;,
 2.83915;-0.30292;0.02855;,
 -2.31157;-0.30292;0.02855;,
 -2.83915;-0.30292;0.02855;,
 -2.83915;5.29671;0.02855;,
 -2.31157;5.29671;0.02855;,
 -2.83915;-0.30292;0.02855;,
 -2.83915;-0.30292;0.81482;,
 -2.83915;5.29671;0.81482;,
 -2.83915;5.29671;0.02855;,
 -2.83915;-0.30292;0.81482;,
 -2.31157;-0.30292;0.81482;,
 -2.31157;5.29671;0.81482;,
 -2.83915;5.29671;0.81482;,
 -2.31157;-0.30292;0.81482;,
 -2.31157;-0.30292;0.02855;,
 -2.31157;5.29671;0.02855;,
 -2.31157;5.29671;0.81482;,
 -2.31157;5.29671;0.02855;,
 -2.83915;5.29671;0.02855;,
 -2.83915;-0.30292;0.02855;,
 -2.31157;-0.30292;0.02855;;
 
 218;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;27,26,28,29;,
 4;29,28,30,31;,
 4;31,30,32,4;,
 4;33,34,35,8;,
 4;36,37,34,33;,
 4;38,39,37,36;,
 4;40,41,39,38;,
 4;42,43,44,0;,
 4;45,46,43,42;,
 4;47,48,46,45;,
 4;49,50,48,47;,
 4;51,52,53,54;,
 4;54,53,55,56;,
 4;56,55,57,58;,
 4;58,57,59,12;,
 4;25,44,60,61;,
 4;61,60,62,63;,
 4;63,62,64,65;,
 4;65,64,16,66;,
 4;52,35,67,68;,
 4;68,67,69,70;,
 4;70,69,71,72;,
 4;72,71,73,74;,
 4;0,24,75,76;,
 4;76,75,77,78;,
 4;78,77,79,80;,
 4;80,79,81,82;,
 4;8,51,83,84;,
 4;84,83,85,86;,
 4;86,85,87,88;,
 4;88,87,20,89;,
 4;41,32,90,91;,
 4;91,90,92,93;,
 4;93,92,94,95;,
 4;95,94,66,73;,
 4;50,59,96,97;,
 4;97,96,98,99;,
 4;99,98,100,101;,
 4;101,100,74,16;,
 4;4,40,102,103;,
 4;103,102,104,105;,
 4;105,104,106,107;,
 4;107,106,89,81;,
 4;12,49,108,109;,
 4;109,108,110,111;,
 4;111,110,112,113;,
 4;113,112,82,20;,
 3;25,61,26;,
 3;61,63,114;,
 3;114,26,61;,
 3;26,114,28;,
 3;63,65,115;,
 3;115,114,63;,
 3;114,115,116;,
 3;116,28,114;,
 3;28,116,30;,
 3;65,66,94;,
 3;94,115,65;,
 3;115,94,92;,
 3;92,116,115;,
 3;116,92,90;,
 3;90,30,116;,
 3;30,90,32;,
 3;27,75,24;,
 3;117,77,75;,
 3;75,27,117;,
 3;29,117,27;,
 3;118,79,77;,
 3;77,117,118;,
 3;119,118,117;,
 3;117,29,119;,
 3;31,119,29;,
 3;107,81,79;,
 3;79,118,107;,
 3;105,107,118;,
 3;118,119,105;,
 3;103,105,119;,
 3;119,31,103;,
 3;4,103,31;,
 3;34,67,35;,
 3;120,69,67;,
 3;67,34,120;,
 3;37,120,34;,
 3;121,71,69;,
 3;69,120,121;,
 3;122,121,120;,
 3;120,37,122;,
 3;39,122,37;,
 3;95,73,71;,
 3;71,121,95;,
 3;93,95,121;,
 3;121,122,93;,
 3;91,93,122;,
 3;122,39,91;,
 3;41,91,39;,
 3;43,60,44;,
 3;123,62,60;,
 3;60,43,123;,
 3;46,123,43;,
 3;124,64,62;,
 3;62,123,124;,
 3;125,124,123;,
 3;123,46,125;,
 3;48,125,46;,
 3;101,16,64;,
 3;64,124,101;,
 3;99,101,124;,
 3;124,125,99;,
 3;97,99,125;,
 3;125,48,97;,
 3;50,97,48;,
 3;8,84,33;,
 3;84,86,126;,
 3;126,33,84;,
 3;33,126,36;,
 3;86,88,127;,
 3;127,126,86;,
 3;126,127,128;,
 3;128,36,126;,
 3;36,128,38;,
 3;88,89,106;,
 3;106,127,88;,
 3;127,106,104;,
 3;104,128,127;,
 3;128,104,102;,
 3;102,38,128;,
 3;38,102,40;,
 3;52,68,53;,
 3;68,70,129;,
 3;129,53,68;,
 3;53,129,55;,
 3;70,72,130;,
 3;130,129,70;,
 3;129,130,131;,
 3;131,55,129;,
 3;55,131,57;,
 3;72,74,100;,
 3;100,130,72;,
 3;130,100,98;,
 3;98,131,130;,
 3;131,98,96;,
 3;96,57,131;,
 3;57,96,59;,
 3;0,76,42;,
 3;76,78,132;,
 3;132,42,76;,
 3;42,132,45;,
 3;78,80,133;,
 3;133,132,78;,
 3;132,133,134;,
 3;134,45,132;,
 3;45,134,47;,
 3;80,82,112;,
 3;112,133,80;,
 3;133,112,110;,
 3;110,134,133;,
 3;134,110,108;,
 3;108,47,134;,
 3;47,108,49;,
 3;54,83,51;,
 3;135,85,83;,
 3;83,54,135;,
 3;56,135,54;,
 3;136,87,85;,
 3;85,135,136;,
 3;137,136,135;,
 3;135,56,137;,
 3;58,137,56;,
 3;113,20,87;,
 3;87,136,113;,
 3;111,113,136;,
 3;136,137,111;,
 3;109,111,137;,
 3;137,58,109;,
 3;12,109,58;,
 4;138,139,140,141;,
 4;142,143,144,145;,
 4;146,147,148,149;,
 4;150,151,152,153;,
 4;150,143,154,155;,
 4;156,157,144,153;,
 4;158,159,160,161;,
 4;162,163,164,165;,
 4;166,167,168,169;,
 4;170,171,172,173;,
 4;174,175,164,173;,
 4;170,163,176,177;,
 4;178,179,180,181;,
 4;182,183,184,185;,
 4;186,187,188,189;,
 4;190,191,192,193;,
 4;194,195,184,193;,
 4;190,183,196,197;,
 4;198,199,200,201;,
 4;202,203,204,205;,
 4;206,207,208,209;,
 4;210,211,212,213;,
 4;210,203,214,215;,
 4;216,217,204,213;,
 4;218,219,220,221;,
 4;222,223,224,225;,
 4;226,227,228,229;,
 4;230,231,232,233;,
 4;230,223,234,235;,
 4;236,237,224,233;,
 4;238,239,240,241;,
 4;242,243,244,245;,
 4;246,247,248,249;,
 4;250,251,252,253;,
 4;254,255,244,253;,
 4;250,243,256,257;;
 
 MeshMaterialList {
  3;
  218;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.276000;0.276000;0.276000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.144000;0.332800;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  132;
  -0.080572;0.995271;0.054256;,
  0.080570;0.995271;0.054256;,
  -0.080572;0.995271;-0.054255;,
  0.080570;0.995271;-0.054255;,
  -0.141669;0.171237;-0.974991;,
  0.141665;0.171237;-0.974992;,
  -0.141669;-0.171235;-0.974992;,
  0.141665;-0.171235;-0.974992;,
  -0.080553;-0.995273;-0.054242;,
  0.080550;-0.995274;-0.054242;,
  -0.080553;-0.995273;0.054243;,
  0.080550;-0.995274;0.054243;,
  -0.141666;-0.171231;0.974993;,
  0.141662;-0.171231;0.974993;,
  -0.141666;0.171233;0.974992;,
  0.141662;0.171233;0.974993;,
  0.990755;0.118610;0.065846;,
  0.990755;-0.118608;0.065846;,
  0.990755;0.118610;-0.065845;,
  0.990755;-0.118608;-0.065845;,
  -0.990756;-0.118604;0.065844;,
  -0.990756;0.118606;0.065843;,
  -0.990756;-0.118604;-0.065843;,
  -0.990756;0.118606;-0.065843;,
  -0.129538;0.967156;-0.218700;,
  0.129536;0.967156;-0.218700;,
  -0.156224;0.853363;-0.497358;,
  0.156222;0.853364;-0.497358;,
  -0.177571;0.541969;-0.821425;,
  0.177568;0.541970;-0.821424;,
  -0.129543;-0.967152;-0.218712;,
  0.129541;-0.967153;-0.218712;,
  -0.156226;-0.853358;-0.497366;,
  0.156225;-0.853359;-0.497366;,
  -0.177571;-0.541971;-0.821423;,
  0.177568;-0.541973;-0.821423;,
  -0.129538;0.967156;0.218700;,
  0.129536;0.967156;0.218700;,
  -0.156224;0.853363;0.497358;,
  0.156223;0.853363;0.497358;,
  -0.177569;0.541964;0.821428;,
  0.177566;0.541965;0.821428;,
  -0.129543;-0.967152;0.218712;,
  0.129541;-0.967153;0.218712;,
  -0.156226;-0.853358;0.497366;,
  0.156225;-0.853358;0.497367;,
  -0.177569;-0.541967;0.821426;,
  0.177566;-0.541968;0.821426;,
  0.314186;0.945494;0.085607;,
  0.314186;0.945494;-0.085606;,
  0.645434;0.758132;0.093010;,
  0.645436;0.758130;-0.093010;,
  0.904574;0.416893;0.089144;,
  0.904573;0.416895;-0.089145;,
  0.314200;-0.945489;0.085610;,
  0.314200;-0.945489;-0.085609;,
  0.645445;-0.758122;0.093011;,
  0.645447;-0.758121;-0.093011;,
  0.904572;-0.416897;0.089144;,
  0.904571;-0.416899;-0.089144;,
  -0.314187;0.945494;0.085606;,
  -0.314187;0.945494;-0.085605;,
  -0.645429;0.758137;0.093007;,
  -0.645430;0.758136;-0.093007;,
  -0.904575;0.416891;0.089140;,
  -0.904574;0.416893;-0.089141;,
  -0.314201;-0.945489;0.085609;,
  -0.314201;-0.945489;-0.085608;,
  -0.645440;-0.758128;0.093008;,
  -0.645441;-0.758126;-0.093008;,
  -0.904573;-0.416895;0.089140;,
  -0.904572;-0.416896;-0.089141;,
  0.475626;-0.202620;-0.855994;,
  0.475626;0.202623;-0.855993;,
  0.813047;-0.165522;-0.558173;,
  0.813046;0.165524;-0.558173;,
  0.955834;-0.151051;-0.252122;,
  0.955833;0.151053;-0.252122;,
  0.475621;-0.202617;0.855997;,
  0.475621;0.202619;0.855996;,
  0.813046;-0.165514;0.558177;,
  0.813046;0.165516;0.558177;,
  0.955835;-0.151045;0.252122;,
  0.955835;0.151047;0.252122;,
  -0.475628;-0.202616;-0.855993;,
  -0.475628;0.202619;-0.855993;,
  -0.813044;-0.165513;-0.558179;,
  -0.813044;0.165515;-0.558179;,
  -0.955835;-0.151043;-0.252121;,
  -0.955835;0.151045;-0.252121;,
  -0.475624;-0.202613;0.855996;,
  -0.475623;0.202616;0.855996;,
  -0.813043;-0.165506;0.558183;,
  -0.813043;0.165508;0.558183;,
  -0.955836;-0.151036;0.252121;,
  -0.955836;0.151038;0.252121;,
  0.444506;0.842040;-0.305586;,
  0.809034;0.494162;-0.318226;,
  0.527470;0.564647;-0.634783;,
  -0.444504;0.842042;-0.305584;,
  -0.809034;0.494161;-0.318228;,
  -0.527470;0.564643;-0.634786;,
  0.444519;-0.842030;-0.305594;,
  0.809031;-0.494167;-0.318225;,
  0.527468;-0.564652;-0.634780;,
  0.444502;0.842042;0.305586;,
  0.809034;0.494160;0.318229;,
  0.527465;0.564646;0.634788;,
  -0.444516;-0.842032;-0.305593;,
  -0.809032;-0.494166;-0.318227;,
  -0.527468;-0.564648;-0.634784;,
  0.444515;-0.842033;0.305594;,
  0.809031;-0.494165;0.318228;,
  0.527463;-0.564651;0.634785;,
  -0.444499;0.842044;0.305584;,
  -0.809034;0.494159;0.318231;,
  -0.527465;0.564642;0.634791;,
  -0.444512;-0.842035;0.305593;,
  -0.809031;-0.494164;0.318230;,
  -0.527463;-0.564647;0.634788;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  218;
  4;0,1,3,2;,
  4;4,5,7,6;,
  4;8,9,11,10;,
  4;12,13,15,14;,
  4;16,17,19,18;,
  4;20,21,23,22;,
  4;2,3,25,24;,
  4;24,25,27,26;,
  4;26,27,29,28;,
  4;28,29,5,4;,
  4;30,31,9,8;,
  4;32,33,31,30;,
  4;34,35,33,32;,
  4;6,7,35,34;,
  4;36,37,1,0;,
  4;38,39,37,36;,
  4;40,41,39,38;,
  4;14,15,41,40;,
  4;10,11,43,42;,
  4;42,43,45,44;,
  4;44,45,47,46;,
  4;46,47,13,12;,
  4;3,1,48,49;,
  4;49,48,50,51;,
  4;51,50,52,53;,
  4;53,52,16,18;,
  4;11,9,55,54;,
  4;54,55,57,56;,
  4;56,57,59,58;,
  4;58,59,19,17;,
  4;0,2,61,60;,
  4;60,61,63,62;,
  4;62,63,65,64;,
  4;64,65,23,21;,
  4;8,10,66,67;,
  4;67,66,68,69;,
  4;69,68,70,71;,
  4;71,70,20,22;,
  4;7,5,73,72;,
  4;72,73,75,74;,
  4;74,75,77,76;,
  4;76,77,18,19;,
  4;15,13,78,79;,
  4;79,78,80,81;,
  4;81,80,82,83;,
  4;83,82,17,16;,
  4;4,6,84,85;,
  4;85,84,86,87;,
  4;87,86,88,89;,
  4;89,88,22,23;,
  4;12,14,91,90;,
  4;90,91,93,92;,
  4;92,93,95,94;,
  4;94,95,21,20;,
  3;3,49,25;,
  3;49,51,96;,
  3;96,25,49;,
  3;25,96,27;,
  3;51,53,97;,
  3;97,96,51;,
  3;96,97,98;,
  3;98,27,96;,
  3;27,98,29;,
  3;53,18,77;,
  3;77,97,53;,
  3;97,77,75;,
  3;75,98,97;,
  3;98,75,73;,
  3;73,29,98;,
  3;29,73,5;,
  3;24,61,2;,
  3;99,63,61;,
  3;61,24,99;,
  3;26,99,24;,
  3;100,65,63;,
  3;63,99,100;,
  3;101,100,99;,
  3;99,26,101;,
  3;28,101,26;,
  3;89,23,65;,
  3;65,100,89;,
  3;87,89,100;,
  3;100,101,87;,
  3;85,87,101;,
  3;101,28,85;,
  3;4,85,28;,
  3;31,55,9;,
  3;102,57,55;,
  3;55,31,102;,
  3;33,102,31;,
  3;103,59,57;,
  3;57,102,103;,
  3;104,103,102;,
  3;102,33,104;,
  3;35,104,33;,
  3;76,19,59;,
  3;59,103,76;,
  3;74,76,103;,
  3;103,104,74;,
  3;72,74,104;,
  3;104,35,72;,
  3;7,72,35;,
  3;37,48,1;,
  3;105,50,48;,
  3;48,37,105;,
  3;39,105,37;,
  3;106,52,50;,
  3;50,105,106;,
  3;107,106,105;,
  3;105,39,107;,
  3;41,107,39;,
  3;83,16,52;,
  3;52,106,83;,
  3;81,83,106;,
  3;106,107,81;,
  3;79,81,107;,
  3;107,41,79;,
  3;15,79,41;,
  3;8,67,30;,
  3;67,69,108;,
  3;108,30,67;,
  3;30,108,32;,
  3;69,71,109;,
  3;109,108,69;,
  3;108,109,110;,
  3;110,32,108;,
  3;32,110,34;,
  3;71,22,88;,
  3;88,109,71;,
  3;109,88,86;,
  3;86,110,109;,
  3;110,86,84;,
  3;84,34,110;,
  3;34,84,6;,
  3;11,54,43;,
  3;54,56,111;,
  3;111,43,54;,
  3;43,111,45;,
  3;56,58,112;,
  3;112,111,56;,
  3;111,112,113;,
  3;113,45,111;,
  3;45,113,47;,
  3;58,17,82;,
  3;82,112,58;,
  3;112,82,80;,
  3;80,113,112;,
  3;113,80,78;,
  3;78,47,113;,
  3;47,78,13;,
  3;0,60,36;,
  3;60,62,114;,
  3;114,36,60;,
  3;36,114,38;,
  3;62,64,115;,
  3;115,114,62;,
  3;114,115,116;,
  3;116,38,114;,
  3;38,116,40;,
  3;64,21,95;,
  3;95,115,64;,
  3;115,95,93;,
  3;93,116,115;,
  3;116,93,91;,
  3;91,40,116;,
  3;40,91,14;,
  3;42,66,10;,
  3;117,68,66;,
  3;66,42,117;,
  3;44,117,42;,
  3;118,70,68;,
  3;68,117,118;,
  3;119,118,117;,
  3;117,44,119;,
  3;46,119,44;,
  3;94,20,70;,
  3;70,118,94;,
  3;92,94,118;,
  3;118,119,92;,
  3;90,92,119;,
  3;119,46,90;,
  3;12,90,46;,
  4;120,120,120,120;,
  4;121,121,121,121;,
  4;122,122,122,122;,
  4;123,123,123,123;,
  4;124,124,124,124;,
  4;125,125,125,125;,
  4;120,120,120,120;,
  4;123,123,123,123;,
  4;122,122,122,122;,
  4;121,121,121,121;,
  4;124,124,124,124;,
  4;125,125,125,125;,
  4;122,122,122,122;,
  4;121,121,121,121;,
  4;120,120,120,120;,
  4;123,123,123,123;,
  4;124,124,124,124;,
  4;125,125,125,125;,
  4;122,122,122,122;,
  4;123,123,123,123;,
  4;120,120,120,120;,
  4;121,121,121,121;,
  4;124,124,124,124;,
  4;125,125,125,125;,
  4;126,126,126,126;,
  4;127,127,127,127;,
  4;128,128,128,128;,
  4;129,129,129,129;,
  4;130,130,130,130;,
  4;131,131,131,131;,
  4;126,126,126,126;,
  4;129,129,129,129;,
  4;128,128,128,128;,
  4;127,127,127,127;,
  4;130,130,130,130;,
  4;131,131,131,131;;
 }
 MeshTextureCoords {
  258;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;;
 }
}
