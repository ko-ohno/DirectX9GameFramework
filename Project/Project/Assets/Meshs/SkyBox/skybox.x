xof 0303txt 0032

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000, 1.000000, 0.000000,
     0.000000, 1.000000, 0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame Cube {
    FrameTransformMatrix {
       1.000000, 0.000000, 0.000000, 0.000000,
       0.000000, 1.000000, 0.000000, 0.000000,
       0.000000, 0.000000, 1.000000, 0.000000,
       0.000000, 0.000000, 0.000000, 1.000000;;
    }
    Mesh { // Cube mesh
      24;
      -1.000000;-1.000000;-1.000000;,
      -1.000000; 1.000000;-1.000000;,
      -1.000000; 1.000000; 1.000000;,
      -1.000000;-1.000000; 1.000000;,
      -1.000000; 1.000000;-1.000000;,
       1.000000; 1.000000;-1.000000;,
       1.000000; 1.000000; 1.000000;,
      -1.000000; 1.000000; 1.000000;,
       1.000000; 1.000000;-1.000000;,
       1.000000;-1.000000;-1.000000;,
       1.000000;-1.000000; 1.000000;,
       1.000000; 1.000000; 1.000000;,
       1.000000;-1.000000;-1.000000;,
      -1.000000;-1.000000;-1.000000;,
      -1.000000;-1.000000; 1.000000;,
       1.000000;-1.000000; 1.000000;,
      -1.000000; 1.000000;-1.000000;,
      -1.000000;-1.000000;-1.000000;,
       1.000000;-1.000000;-1.000000;,
       1.000000; 1.000000;-1.000000;,
       1.000000; 1.000000; 1.000000;,
       1.000000;-1.000000; 1.000000;,
      -1.000000;-1.000000; 1.000000;,
      -1.000000; 1.000000; 1.000000;;
      6;
      4;3,2,1,0;,
      4;7,6,5,4;,
      4;11,10,9,8;,
      4;15,14,13,12;,
      4;19,18,17,16;,
      4;23,22,21,20;;
      MeshNormals { // Cube normals
        6;
         1.000000; 0.000000; 0.000000;,
         0.000000;-1.000000;-0.000000;,
        -1.000000; 0.000000;-0.000000;,
         0.000000; 1.000000; 0.000000;,
         0.000000; 0.000000; 1.000000;,
         0.000000; 0.000000;-1.000000;;
        6;
        4;0,0,0,0;,
        4;1,1,1,1;,
        4;2,2,2,2;,
        4;3,3,3,3;,
        4;4,4,4,4;,
        4;5,5,5,5;;
      } // End of Cube normals
      MeshTextureCoords { // Cube UV coordinates
        24;
         0.499995; 0.333367;,
         0.749945; 0.333326;,
         0.749976; 0.666593;,
         0.500026; 0.666633;,
         0.749945; 0.333326;,
         0.999895; 0.333285;,
         0.999926; 0.666552;,
         0.749976; 0.666593;,
         0.000095; 0.333448;,
         0.250045; 0.333407;,
         0.250076; 0.666674;,
         0.000126; 0.666715;,
         0.250045; 0.333407;,
         0.499995; 0.333367;,
         0.500026; 0.666633;,
         0.250076; 0.666674;,
         0.499965; 0.000100;,
         0.499995; 0.333367;,
         0.250045; 0.333407;,
         0.250015; 0.000141;,
         0.250106; 0.999941;,
         0.250076; 0.666674;,
         0.500026; 0.666633;,
         0.500056; 0.999900;;
      } // End of Cube UV coordinates
      MeshMaterialList { // Cube material list
        1;
        6;
        0,
        0,
        0,
        0,
        0,
        0;
        Material Material {
           0.800000; 0.800000; 0.800000; 1.000000;;
           96.078431;
           0.000000; 0.000000; 0.000000;;
           0.000000; 0.000000; 0.000000;;
          TextureFilename {"SkyBox/skybox_4K.png";}
        }
      } // End of Cube material list
    } // End of Cube mesh
  } // End of Cube
} // End of Root
