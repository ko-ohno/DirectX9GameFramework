#include "StdAfx.h"
#include "DoxygenCppCommentTemp.h"
/**********************/
/* �t�@�C���w�b�_�̗� */
/**********************/

/******************************************************************************/
/*! @addtogroup ���W���[����_�T�u���W���[����
    @file       comment.c
    @brief      �t�@�C���̊T�v
*******************************************************************************
    �t�@�C���̏ڍׂȐ���
*******************************************************************************
    @date       �쐬��(YYYY/MM/DD)
    @author     �쐬�Җ�
    @par        Revision
    $Id$
    @par        Copyright
    20XX-20XX ABC Company Co., Ltd. All rights reserved.
*******************************************************************************
    @par        History
    - 20XX/01/01 �X�V�Җ�1
      -# Initial Version
    - 20XX/01/02 �X�V�Җ�2
      -# Add xxx function
      -# Delete yyy function
******************************************************************************/

/*! @ingroup ���W���[����_�T�u���W���[���� */
/* @{ */

#include <stdio.h>

/************/
/* ��`�̗� */
/************/

/*! @brief �ȒP�Ȓ�`�̐��� */
#define AAA 123

/*! @brief ��`�̊T�v

    ��`�̏ڍ�
*/
#define BBB 456

#define CCC 758 /*!< ��`�̐��������ɂ��� */

/*! @name ��`�O���[�vX
    �O���[�v��������`�̐���
*/
/* @{ */
#define DDD 9AB /*!< ��`�̐��������ɂ���1 */
#define EEE CDE /*!< ��`�̐��������ɂ���2 */
/* @} */

/**********************/
/* �O���[�o���ϐ��̗� */
/**********************/

/*! @var   global_var1
    @brief �O���[�o���ϐ��̐���
*/
int global_var1;

/*! @var   global_var2
    @brief �O���[�o���ϐ��̐���

    �O���[�o���ϐ��̏ڍ�
*/
int global_var2;

/**************/
/* �\���̗̂� */
/**************/

/*! @struct tStruct1
    @brief  �\���̂̐���
*/
typedef struct {
    /*! �����o1�̐��� */
    int member1;

    int member2; /*!< �����o2�̐��������ɂ��� */
} tStruct1;

/*! @struct tStruct2
    @brief  �\���̂̐���

    �\���̂̏ڍׂȐ���
*/
typedef struct {
} tStruct2;

/**************/
/* �񋓌^�̗� */
/**************/
/*! @enum eEnum1
    @brief  �񋓌^�̐���
*/
typedef enum {
    aaa,

    /*! �񋓌^�̒l�̐��� */
    bbb,

    ccc, /*!< �񋓌^�̒l�̐��������ɂ���� */
} eEnum1;

/*! @enum eEnum2
    @brief  �񋓌^�̐���

    �񋓌^�̏ڍׂȐ���
*/
typedef enum {
} eEnum2;

/**************/
/* �N���X�̗� */
/**************/

/*! @class Class1
    @brief  �N���X�̐���
*/
class Class1 {
public:
    /*! �����o1�̐��� */
    int member1;

    int member2; /*!< �����o2�̐��������ɂ��� */

    /*! ���\�b�h1�̐��� */
    int method1(int var1, int var2);

    /*! ���\�b�h2�̐����B�ڍא���
        @param[out]     var1    var1�̐���
        @param[in]      var2    var2�̐���
        @param[in,out]  var3    var3�̐���
        @par            Refer
        - �Q�Ƃ���O���[�o���ϐ� global_var1
        - �Q�Ƃ���O���[�o���ϐ� global_var2
        @par            Modify
        - �ύX����O���[�o���ϐ� global_var3
        - �ύX����O���[�o���ϐ� global_var4
        @return         ���� 0, ���s 0 �ȊO �Ȃ�
        @exception      ��O�B�s�v�ł����none���L�q
    */
    int method2(int var1, int var2, int var3) {

    }
};

/*! @class Class2
    @brief  �N���X�̐���

    �N���X�̏ڍ�
*/
class Class2 : public Class1 {
};

/************/
/* �֐��̗� */
/************/

/******************************************************************************/
/*! @brief �֐��̊T�v

    �K�v�ł���ΏڍׂȐ���
    @param[out]     var1    var1�̐���
    @param[in]      var2    var2�̐���
    @param[in,out]  var3    var3�̐���
    @par            Refer
    - �Q�Ƃ���O���[�o���ϐ� global_var1
    - �Q�Ƃ���O���[�o���ϐ� global_var2
    @par            Modify
    - �ύX����O���[�o���ϐ� global_var3
    - �ύX����O���[�o���ϐ� global_var4
    @return         ���� 0, ���s 0 �ȊO �Ȃ�
    @exception      ��O�B�s�v�ł����none���L�q
******************************************************************************/
int func(int var1, char* var2, char* var3[])
{
    return 0;
}

/* @} */