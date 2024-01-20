<template>
  <div class="back">
    <div class="profile">
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
      <div class="body">
        <profile-navbar class="profileNavbar"></profile-navbar>
        <div class="form_for_btn_new"><router-link :to="{ name: 'newEvents'}"><button class="btn_new">New</button></router-link></div>
        <div class="container_for_event_forms">
          <event-form></event-form>
          <event-form></event-form>
          <event-form></event-form>
          <event-form></event-form>
          <event-form></event-form>
          <event-form></event-form>
          <event-form></event-form>
          <event-form></event-form>
          <event-form></event-form>
          <event-form></event-form>
          <event-form></event-form>
          <event-form></event-form>
          <event-form></event-form>
          <event-form></event-form>
        </div>
      </div>
    </div>
  </div>

</template>
<script>
  import MyButton from "@/components/UI/MyButton.vue";
  import ProfileNavbar from "@/components/UI/ProfileNavbar.vue";
  import EventForm from "@/components/UI/EventForm.vue";
  export default {
    components: {EventForm, ProfileNavbar, MyButton},
  }
</script>

<style scoped>
hr {
  margin-top: 5px;
  background-color: #858585;
  padding: .3px;
  border: #858585;
}

.back {
  background-color: #0d1117;
  position: fixed;
  width: 100vw;
  max-height: 100vh;
  height: 100vh;
  padding: 80px 5% 24px 5%;
  overflow-y: auto;
  overflow-x: hidden;

}

.profile {
  position: absolute;
  //border: 1px solid red;
  width: 85vw;
  height: 100%;
}
.info{
  position: absolute;
  top: 0;
  left: 0;
  //border: 1px solid #31a0a8;
  width: 25%;
  height: 80vh;
  padding: 2%;
}
.body{
  position: absolute;
  top: 0;
  left: 25%;
  //border: 1px solid #cfcfcf;
  width: 75%;
  height: 80vh;
  padding: 0 10px 10px 10px;
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
  color: #0e73bd;
  //border: 1px solid red;
  font-size: 22px;
}
.user_info {
  margin-top: 10px;
  color: #cfcfcf;
  //border: 1px solid red;
  display: flex;
  gap: 20%;
  justify-content: center;
}
.user_description {
  margin-top: 10px;
  color: #858585;
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

.btn_new {
  font-size: 14px;
  letter-spacing: 1px;
  background: #587DFF;
  padding: 2px 5px;
  text-decoration: none;
//text-transform: uppercase;
  border-radius: 5px;
  transition: .6s;
  border: none;
  cursor: pointer;
  right: 10px;
  width: 60px;
  height: 30px;
  position: absolute;
}

.btn_new:hover {
  background-color: #31a0a8;
}
.form_for_btn_new{
  width: 870px;
  height: 40px;
  margin-bottom: 5px;
}
.container_for_event_forms{
  width: 100%;
  padding: 0 0 15px 10px;
  //border: 1px solid red;
  display: grid;
  align-content: start;
  grid-template-columns: repeat(2, 1fr);
}


@media (max-width: 992px) {
  .back{
    overflow-y: auto;
    overflow-x: hidden;
  }
  .container_for_event_forms{

    grid-template-columns: repeat(1, 1fr);
  }
  .profileNavbar{
    gap: 20px;
    font-size: 14px;
  }

}
@media (max-width: 768px) {
  .back{
    overflow-y: auto;
    overflow-x: hidden;
  }
  .info{
    top: 0;
    left: 0;
    width: 100%;
    height: 30%;
    display: flex;
    flex-direction: row;
    gap: 5px;
  }
  .body{
    top: 30%;
    left: 0;
    width: 100%;
    height: 70%;
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
    color: #858585;
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