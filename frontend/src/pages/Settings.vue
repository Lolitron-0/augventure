<template>
  <div class="back">
    <div class="settings">
      <info-block-for-profile v-bind:nickname.sync="user.username" :bio="user.bio" :photo="user.pfp_url"/>
      <div class="body">
        <profile-navbar class="profileNavbar"></profile-navbar>

        <div class="form_picture">
          <p class="picture_text">Profile picture</p>
          <div class="form_for_picture">
            <input type="file" id="file" accept="image/png, image/gif, image/jpeg"
                   name="logo_for_profile" class="input_form_for_picture">
            <img :src="user.pfp_url" alt="" class="ellipse_logo"/>
            <div class="TextBlock_in_container">
              <label for="file" class="label_for_picture">
                <p class="text_in_containerPicture">Download</p>
              </label>
              <p class="text_in_containerPicture">Remove</p>
            </div>
          </div>
        </div>

        <div class="block_about_private_information">
          <input type="text" class="input_form_for_name" :placeholder="profileData.username"
                 v-model.trim="profileData.username">
          <textarea name="message" rows="15" cols="50" :placeholder="profileData.bio"
                    class="textarea_form_for_aboutMe" v-model.trim="profileData.bio"></textarea>
          <div class="container_for_btn">
            <my-button class="btn_save" v-on:click="this.updateProfile">Save changes</my-button>
          </div>
        </div>

        <div class="block_about_email">
          <p class="text_for_email">Your mailling addresses</p>
          <div class="current_email">
            <email-form></email-form>
            <email-form></email-form>
            <email-form></email-form>
          </div>
          <input type="email" class="input_for_email" placeholder="New mailling addresses">
          <div class="container_for_btn_addEmail">
            <my-button class="btn_addEmail">Add email</my-button>
          </div>
        </div>

        <div class="block_about_password">
          <p class="new_password_title">New password</p>
          <input type="password" class="input_form_for_password" placeholder="Current password">
          <input type="password" class="input_form_for_password" placeholder="New password">
          <input type="password" class="input_form_for_password" placeholder="New password(repeat)">
          <div class="block_for_btn_savePassword">
            <my-button class="btn_savePassword">Save changes</my-button>
          </div>
          <p class="forget_password_title">Forget password?</p>
          <p class="text_forget_password">Enter your email address, and we will send you an email with which you can
            reset your password.</p>
          <input type="email" class="input_form_for_email" placeholder="Email address">
          <div class="block_for_btn_savePassword">
            <my-button class="btn_savePassword">Send</my-button>
          </div>
        </div>

        <div class="block_about_deleteAccount">
          <p class="title_delete_account">Delete account</p>
          <p class="text_warning">Once you delete your account, there is no going back. Please be certain.</p>
          <div class="block_for_btn_delete">
            <my-button class="btn_delete_account">Delete your account</my-button>
          </div>
        </div>

        <!--        <div class="modal">-->
        <!--          <div class="modal_box">-->
        <!--            <h3 class="modal_title">-->
        <!--              Do you want to delete your account? There will be no turning back. Please rest assured.-->
        <!--            </h3>-->
        <!--            <my-button class="btn_delete_modalBox">Delete</my-button>-->
        <!--          </div>-->
        <!--        </div>-->
      </div>
    </div>
  </div>
</template>

<script>
import MyButton from "@/components/UI/MyButton.vue";
import ProfileNavbar from "@/components/UI/ProfileNavbar.vue";
import EventForm from "@/components/UI/EventForm.vue";
import EmailForm from "@/components/UI/EmailForm.vue";
import InfoBlockForProfile from "@/components/InfoBlockForProfile.vue";
import profile from "@/pages/Profile.vue";
import FormData from 'form-data'

export default {
  components: {InfoBlockForProfile, EmailForm, MyButton, EventForm, ProfileNavbar},

  data() {
    let user = JSON.parse(localStorage.getItem('user'));
    return {
      user: user,
      profileData: {
        username: user.username,
        bio: user.bio,
      }
    }
  },
  methods: {
    async updateProfile() {
      try {
        console.log(this)
        const response = await this.$api.users.updateProfile({
          username: this.profileData.username,
          bio: this.profileData.bio
        });
        this.user.username = this.profileData.username
        this.user.bio = this.profileData.bio
        localStorage.setItem('user', JSON.stringify(this.user));
      } catch (error) {
        console.log(error.message);
      }
      try {
        if (document.getElementById("file").files.length) {
          let file = document.getElementById("file").files[0];
          let data = new FormData();
          data.append('file', file, file.name);
          const response = await this.$api.users.uploadPFP(data, {
            headers: {
              'accept': 'application/json',
              'Accept-Language': 'en-US,en;q=0.8',
              'Content-Type': `multipart/form-data; boundary=${data._boundary}`,
            }
          });
          this.user.pfp_url = response.data.pfp_url;
          localStorage.setItem('user', JSON.stringify(this.user));
        }
      } catch (error) {
        console.log(error.message);
      }
    },
  },
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

.settings {
  position: absolute;
  //border: 1px solid red;
  width: 85vw;
  height: 80vh;
}

.info {
  position: absolute;
  top: 0;
  left: 0;
  //border: 1px solid #31a0a8;
  width: 25%;
  height: 80vh;
  padding: 2%;
}

.body {
  position: absolute;
  top: 0;
  left: 25%;
  //border: 1px solid #cfcfcf;
  width: 75%;
  padding: 0 10px 50px 10px;
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

.profile_nickname {
  margin-top: 10px;
  color: #0e73bd;
  //border: 1px solid red;
  font-size: 22px;
}

.profileNavbar {
  margin-bottom: 20px;
}

.input_form_for_name, .input_form_for_surname {
  padding: 0 10px;
  color: var(--text-wight-color);
  width: 100%;
  height: 30px;
  background-color: var(--background-app-color);
  border: 1px solid var(--border-light-gray-color);
  margin-bottom: 15px;
}

.textarea_form_for_aboutMe {
  padding: 0 10px;
  color: var(--text-wight-color);
  width: 100%;
  height: 80px;
  background-color: var(--background-app-color);
  border: 1px solid var(--border-light-gray-color);
  margin-bottom: 15px;
  resize: vertical;
  overflow: auto;
}

.container_for_btn {
  width: 100%;
  //border: 1px solid red;
  justify-content: right;
  display: flex;
}

.btn_save {
  width: 200px;
  height: 30px;
  border: none;
  justify-content: center;
  align-items: center;
  color: var(--text-wight-color);

}

.block_about_private_information {
  border-bottom: 1px solid var(--border-dark-gray-color);
  padding-bottom: 15px;
}

.form_picture {
  width: 100%;
  //border: 1px solid #31a0a8;
  border-bottom: 1px solid var(--border-dark-gray-color);
  padding-bottom: 15px;
  margin-top: 15px;
  margin-bottom: 15px;
}

.picture_text {
  font-size: 16px;
  color: var(--title-color);
  font-weight: 300;
}

.form_for_picture {
  width: 100%;
  height: 160px;
  border: 1px solid var(--border-light-gray-color);
  justify-content: center;
  align-items: center;
  display: flex;
  margin-top: 10px;
  padding: 0;
  left: 150px;
}

.input_form_for_picture {
  width: 0;
  height: 0;
  position: absolute;
  //background-color: #858585;
  opacity: 0;
  z-index: -1;
  cursor: pointer;
}

.label_for_picture {
  //background-color: #cfcfcf;
  justify-content: space-between;
  align-items: center;
  display: flex;

  cursor: pointer;
}

.ellipse_logo {
  height: 90%;
  border: 1px solid #858585;
  box-sizing: border-box;
  background-color: #0e73bd;
  cursor: pointer;
  border-radius: 50%;
  aspect-ratio: 1;
}

.TextBlock_in_container {
  color: var(--text-wight-color);
  //border: 1px solid red;
  width:  80%;
  height: 100%;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  gap: 35px;
}

.text_in_containerPicture {
  font-size: 18px;
  transition: .3s;
  cursor: pointer;
}

.text_in_containerPicture:hover {
  color: var(--text-turquoise-color)
}

.block_about_email {
  width: 100%;
  //border: 1px solid red;
  border-bottom: 1px solid var(--border-dark-gray-color);
  padding-bottom: 15px;
  margin-bottom: 15px;
}

.text_for_email {
  color: var(--text-wight-color);
  font-size: 18px;
  padding-bottom: 10px;
}

.input_for_email {
  margin-top: 15px;
  width: 100%;
  height: 40px;
  background-color: var(--background-app-color);
  border: 1px solid var(--border-light-gray-color);
  padding-left: 10px;
  color: var(--text-wight-color);
}

.container_for_btn_addEmail {
  margin-top: 10px;
  width: 100%;
  //border: 1px solid red;
  display: flex;
  justify-content: right;
}

.btn_addEmail {
  border: none;
  width: 200px;
  height: 30px;
  justify-content: center;
  align-items: center;
  color: var(--text-wight-color);
}

.block_about_password {
  width: 100%;
  //border: 1px solid red;
  padding-bottom: 5px;
  border-bottom: 1px solid #24292F;
}

.new_password_title, .forget_password_title {
  color: var(--text-wight-color);
  font-size: 18px;
  margin-bottom: 10px;
}

.input_form_for_password {
  width: 100%;
  background-color: var(--background-app-color);
  height: 40px;
  border: 1px solid var(--border-light-gray-color);
  margin-bottom: 10px;
  padding-left: 10px;
  color: var(--text-wight-color);
  font-size: 17px;
}

.block_for_btn_savePassword {
  width: 100%;
  //border: 1px solid red;
  display: flex;
  justify-content: right;
  margin-bottom: 10px;
}

.btn_savePassword {
  width: 200px;
  height: 30px;
  border: none;
  color: var(--text-wight-color);
  justify-content: center;
  align-items: center;
}

.text_forget_password {
  color: var(--text-wight-color);
  margin-bottom: 10px;
  font-size: 16px;
}

.input_form_for_email {
  width: 100%;
  background-color: var(--background-app-color);
  padding-left: 10px;
  height: 40px;
  border: 1px solid var(--border-light-gray-color);
  color: var(--text-wight-color);
  margin-bottom: 10px;
}

.block_about_deleteAccount {
  width: 100%;
  display: flex;
  justify-content: center;
  padding: 15px 0;
  flex-direction: column;
  //border: 1px solid red;
  gap: 15px;
}

.title_delete_account {
  font-size: 20px;
  color: red;
  justify-content: center;
  display: flex;
}

.text_warning {
  font-size: 18px;
  color: var(--text-wight-color);
  justify-content: center;
  display: flex;
}

.block_for_btn_delete {
  width: 100%;
  justify-content: center;
  display: flex;
}

.btn_delete_account {
  width: 300px;
  color: red;
  border: none;
  height: 40px;
  justify-content: center;
  align-items: center;
  font-size: 18px;
}

/*.modal{
  position: fixed;
  left: 0;
  top: 0;
  width: 100%;
  height: 100vh;
  background-color: rgba(0, 0, 0, .4);
  display: grid;
  align-items: center;
  justify-content: center;
  visibility: hidden;
  opacity: 0;
  transition: opacity .4s, visibility .4s;
}
.modal.open {
  visibility: visible;
  opacity: 1;
}
.modal_box{
  max-width: 500px;
  padding: 45px;
  background-color: #858585;
  gap: 50px;
  overflow: auto;
  justify-content: center;
  align-items: center;
  display: flex;
  flex-direction: column;
  transform: scale(0);
  transition: transform .8s;
}
.modal.open .modal_box{
  transform: scale(1);
}

.btn_delete_modalBox{
  border: none;
  width: 200px;
  height: 30px;
  align-items: center;
  justify-content: center;
  color: red;
  font-size: 18px;
}*/
@media (max-width: 992px) {
  .info {
    //border: 1px solid #31a0a8;
    width: 0;
    height: 0;
    opacity: 0;
  }

  .body {
    left: 0;
    //border: 1px solid #cfcfcf;
    width: 100%;
    padding: 0 0 50px 0;
  }

  .btn_addEmail, .btn_savePassword,
  .btn_save {
    width: 180px;
  }

  .btn_delete_account {
    width: 200px;
    font-size: 16px;
  }

  .TextBlock_in_container {
    width: 100%;
    border: 1px solid red;
  }
}

@media (max-width: 800px) {
  .btn_addEmail, .btn_savePassword,
  .btn_save {
    width: 180px;
  }

  .btn_delete_account {
    width: 200px;
    font-size: 16px;
  }
}
</style>