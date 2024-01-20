<template>
  <div class="info">
    <div class="min_fersion">
      <div class="ellipse_nav_logo"></div>
      <div class="profile_nickname">Nickname</div>
    </div>
    <hr class="first_hr">
    <div class="user_info">
      <div class="your_subscribers">
        <i class="ri-user-star-line"></i>
        23.1k
      </div>
      <div class="profile_info_users_events">
        <i class="ri-git-branch-line"></i>
        24
      </div>
      <div class="subscriptions">
        <i class='bx bxs-star'></i>
        98
      </div>
    </div>
    <hr>
    <div class="user_description">
      Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores
    </div>
  </div>
</template>

<script>
export default {

}
</script>

<style scoped>
@import "@/styles.css";

.info{
  position: absolute;
  top: 0;
  left: 0;
//border: 1px solid #31a0a8;
  width: 25%;
  height: 80vh;
  padding: 2%;
}

.ellipse_nav_logo {
  width: 90%;
  height: 0;
  padding-bottom: 90%;
  max-width: 256px;
  max-height: 256px;
  border: solid 1px #858585;
  box-sizing: border-box;
  background-color: #0e73bd;
  cursor: pointer;
  border-radius: 50%;
}

.profile_nickname{
  margin-top: 10px;
  color: var(--profile-nickname);
//border: 1px solid red;
  font-size: 22px;
}
.user_info {
  margin-top: 10px;
  color: var(--user-info);
//border: 1px solid red;
  display: flex;
  gap: 20%;
  justify-content: center;
}
.user_description {
  margin-top: 10px;
  color: var(--user-description);
//border: 1px solid red;
  font-size: 14px;
}

.your_subscribers{
  display: flex;
  flex-direction: column;
}

.profile_info_users_events {
  display: flex;
  flex-direction: column;
}

.subscriptions {
  display: flex;
  flex-direction: column;
}

@media (max-width: 768px) {

  .info{
    top: 0;
    left: 0;
    width: 100%;
    height: 30%;
    display: flex;
    flex-direction: row;
    gap: 5px;
  }
  .ellipse_nav_logo {
    width: 130px;
    height: 130px;
    padding-bottom: 0;
  }
  .profile_nickname{
    margin-left: 0;
  //border: 1px solid red;
    top: 20%;
    font-size: 20px;
  }
  .first_hr{
    display: none;
  }
  .user_info {
  //border: 1px solid red;
    margin-top: 0;
    gap: 25px;
    display: flex;
    flex-direction: column;
    align-items: flex-start;
  }
  .user_description {
    margin-top: 0;
    padding: 5px;
    color: var(--user-description);
  //border: 1px solid red;
    font-size: 14px;
    flex: 1;
  }

  .your_subscribers, .profile_info_users_events, .subscriptions{
    display: flex;
    gap: 5px;
    flex-direction: row;
  }

}
</style>