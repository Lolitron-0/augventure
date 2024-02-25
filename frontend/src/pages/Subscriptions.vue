<template>
  <div class="back">
    <div class="subscriptions">
      <info-block-for-profile :nickname="user.username" :bio="user.bio" :photo="user.pfp_url"/>
      <div class="body">
        <profile-navbar class="profileNavbar"></profile-navbar>
      </div>
    </div>
  </div>
</template>

<script>
import ProfileNavbar from "@/components/UI/ProfileNavbar.vue";
import InfoBlockForProfile from "@/components/InfoBlockForProfile.vue";

export default {
  components: {InfoBlockForProfile, ProfileNavbar},

  data() {
    const user = JSON.parse(localStorage.getItem('user'));
    return {
      user: user,
      events: [],
    }
  }
}
</script>

<style scoped>
@import "@/styles.css";

.back {
  background-color: var(--background-app-color);
  position: fixed;
  width: 100vw;
  max-height: 100vh;
  height: 100vh;
  padding: 80px 5% 24px 5%;
  overflow-y: auto;
  overflow-x: hidden;

}

.subscriptions {
  position: absolute;
//border: 1px solid red;
  width: 85vw;
  height: 80vh;
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
</style>