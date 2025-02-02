## 보스전 구현
---
# 중요도

- 높음 : 구현되어야 하는 부분 : VI

-	중간 : 변경될 수 있음 : C

-	낮음 : 변경 또는 삭제될 수 있음 : D
---
# 보스 구현

-	AI 추가

    -	맵 내부에서 돌아다니며 정해진 패턴으로 일정한(랜덤성의) 공격 : VI

        -	공격 종류는 정해져있지만 그 공격은 랜덤으로 발생 : VI
  
-	보스 패턴 추가
  
      -	전방 공격 : VI
  
      -	보스 주변 원형 공격 : C
  
      -	보스에서 일정 범위 떨어진 거리에 원형 공격 : C
  
        -	보스 주변 원형 공격 이후에 바로 이어짐 : D
---
# 맵 패턴 구현

-	운석 패턴

      - 맵 전체에 랜덤으로 낙하물 구현 : VI

      - 보스의 체력에 따라 낙하물의 종류가 달라짐 : C

      -	보스의 체력에 따라 낙하물의 양이 달라짐 : C
---
# 캐릭터의 구현

-	캐릭터의 시야

      -	탑다운뷰 : VI

      -	카메라 캐릭터 위 고정 : VI

-	캐릭터의 이동

      -	방향키로 이동 : VI
    
      -	점프 : VI

        -	더블 점프 : D

-	회피기(텔레포트 또는 구르기) or 공격하며 이동 : D

-	캐릭터의 공격

      -	근접공격 기반 : VI

      -	쿨타임이 있는 스킬 2~3개 

        -	짧은 쿨타임을 가지는 약한 공격 스킬 : C

        -	긴 쿨타임을 가지는 강한 공격 스킬 : C

        -	그로기를 만들 수 있는 반격 스킬 : D



